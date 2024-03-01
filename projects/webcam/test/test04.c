#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <sys/mman.h>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>

#include <linux/videodev2.h>

#define OUTPUT_WIDTH 1280
#define OUTPUT_HEIGHT 720
#define OUTPUT_FPS 30

int main(int argc, char *argv[])
{
    int fd = open("/dev/video0", O_RDWR);
    if (1)
    {
        // 输出所有支持的格式
        struct v4l2_fmtdesc fmtdesc;
        fmtdesc.index = 0;
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        printf("Support format:\n");
        while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)

        {
            printf("\t%d.%s\n", fmtdesc.index + 1, fmtdesc.description);
            fmtdesc.index++;
        }
        printf("enum done\n");
    }
    if (1)
    {
        // 查看当前的输出格式
        struct v4l2_format fmt;
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ioctl(fd, VIDIOC_G_FMT, &fmt);

        printf("Current data format information : \n\twidth: % d\n\theight: % d\n", fmt.fmt.pix.width, fmt.fmt.pix.height);

        struct v4l2_fmtdesc fmtdesc2;
        fmtdesc2.index = 0;
        fmtdesc2.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc2) != -1)
        {
            if (fmtdesc2.pixelformat & fmt.fmt.pix.pixelformat)
            {
                printf("\tformat: % s\n", fmtdesc2.description);
                break;
            }
            fmtdesc2.index++;
        }
    }
    {
        // 设置视频格式
        struct v4l2_format fmt;
        memset(&fmt, 0, sizeof(fmt));
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = 1280;
        fmt.fmt.pix.height = 720;
        fmt.fmt.pix.pixelformat = 0;
        fmt.fmt.pix.field = V4L2_FIELD_ANY;
        // 设置设备捕获视频的格式
        if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0)
        {
            printf("set format failed\n");
            close(fd);
            return 0;
        }
        // 如果摄像头不支持我们设置的分辨率格式，则 fmt.fmt.pix.width 会被修改，所以此处建议再次检查 fmt.fmt.pix. 的各种信息

        // 向驱动申请帧缓存
        int CAP_BUF_NUM = 4;
        struct v4l2_requestbuffers req;
        memset(&req, 0, sizeof(req));
        req.count = CAP_BUF_NUM; // 申请一个拥有四个缓冲帧的缓冲区
        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory = V4L2_MEMORY_MMAP;
        if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0)
        {
            if (EINVAL == errno)
            {
                printf(" does not support memory mapping\n");
                close(fd);
                return 0;
            }
            else
            {
                printf("does not support memory mapping, unknow error\n");
                close(fd);
                return 0;
            }
        }
        else
        {
            printf("alloc success\n");
        }
        if (req.count < CAP_BUF_NUM)
        {
            printf("Insufficient buffer memory\n");
            close(fd);
            return 0;
        }
        else
        {
            printf("get %d bufs\n", req.count);
        }

        // 将帧缓存与本地内存关联
        typedef struct VideoBuffer
        { // 定义一个结构体来映射每个缓冲帧
            void *start;
            size_t length;
        } VideoBuffer;
        VideoBuffer *buffers = calloc(req.count, sizeof(*buffers));
        struct v4l2_buffer buf;

        for (int numBufs = 0; numBufs < req.count; numBufs++)
        { // 映射所有的缓存
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = numBufs;
            if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
            { // 获取到对应index的缓存信息，此处主要利用length信息及offset信息来完成后面的mmap操作。
                printf("unexpect error %d\n", numBufs);
                free(buffers);
                close(fd);
                return 0;
            }

            buffers[numBufs].length = buf.length;
            // 转换成相对地址
            buffers[numBufs].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset); // #include <sys/mman.h>
            if (buffers[numBufs].start == MAP_FAILED)
            {
                printf("%d map failed errno %d\n", numBufs, errno);
                free(buffers);
                close(fd);
                return 0;
            }
            // addr 映射起始地址，一般为NULL ，让内核自动选择
            // prot 标志映射后能否被读写，其值为PROT_EXEC,PROT_READ,PROT_WRITE, PROT_NONE
            // flags 确定此内存映射能否被其他进程共享，MAP_SHARED,MAP_PRIVATE
            // fd,offset, 确定被映射的内存地址 返回成功映射后的地址，不成功返回MAP_FAILED ((void*)-1)
            // int munmap(void* addr, size_t length);// 最后记得断开映射

            // 把缓冲帧加入缓冲队列
            if (ioctl(fd, VIDIOC_QBUF, &buf) < 0)
            {
                printf("add buf to queue failed %d\n", numBufs);
                free(buffers);
                close(fd);
                return 0;
            }
        }

        printf("打开设备视频流\n");

        int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        /* 打开设备视频流 */
        if (ioctl(fd, VIDIOC_STREAMON, &type) < 0)
        {
            printf("stream open failed\n");
            free(buffers);
            close(fd);
            return 0;
        }

        // Initialize libx264 encoder
        AVCodec *codec;
        AVCodecContext *c;
        AVFrame *frame;
        AVPacket pkt;
        int ret, got_output;
        uint8_t endcode[] = {0, 0, 1, 0xb7};

        codec = avcodec_find_encoder(AV_CODEC_ID_H264);
        if (!codec)
        {
            fprintf(stderr, "Codec not found\n");
            return EXIT_FAILURE;
        }

        c = avcodec_alloc_context3(codec);
        if (!c)
        {
            fprintf(stderr, "Could not allocate video codec context\n");
            return EXIT_FAILURE;
        }

        // Set codec parameters
        c->bit_rate = 400000;
        c->width = OUTPUT_WIDTH;
        c->height = OUTPUT_HEIGHT;
        c->time_base.num = 1;
        c->time_base.den = OUTPUT_FPS;
        c->gop_size = 10;
        c->max_b_frames = 1;
        c->pix_fmt = AV_PIX_FMT_YUV420P;

        // Open codec
        if (avcodec_open2(c, codec, NULL) < 0)
        {
            fprintf(stderr, "Could not open codec\n");
            return EXIT_FAILURE;
        }

        // Allocate and initialize a frame
        frame = av_frame_alloc();
        if (!frame)
        {
            fprintf(stderr, "Could not allocate video frame\n");
            return EXIT_FAILURE;
        }
        frame->format = c->pix_fmt;
        frame->width = c->width;
        frame->height = c->height;
        frame->pts = 0; // 设置时间戳为 0

        ret = av_frame_get_buffer(frame, 32);
        if (ret < 0)
        {
            fprintf(stderr, "Could not allocate the video frame data\n");
            return EXIT_FAILURE;
        }

        printf("将已经捕获好视频的内存拉出已捕获视频的队列\n");

        int franeCount = 100;
        while (franeCount--)
        {
            struct v4l2_buffer capture_buf;
            memset(&capture_buf, 0, sizeof(capture_buf));
            capture_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            capture_buf.memory = V4L2_MEMORY_MMAP;
            /* 将已经捕获好视频的内存拉出已捕获视频的队列 */
            if (ioctl(fd, VIDIOC_DQBUF, &capture_buf) < 0)
            {
                printf("get frame failed %d\n", franeCount);
                break;
            }
            else
            {
                // long long secc = capture_buf.timestamp.tv_sec;
                // long long secc2 = capture_buf.timestamp.tv_usec;
                // printf("timestamp %lld  %lld", secc, secc2);
                // handle frame
                {
                    FILE *f = fopen("./My_output.yuv", "ab");
                    FILE *f1 = fopen("./MuOutput.mp4","ab");
                    int wt = fwrite(buffers[capture_buf.index].start, 1, buffers[capture_buf.index].length, f);
                    printf("wt %d\n", wt);
                    fclose(f);

                    ret = avcodec_encode_subtitle(c, &pkt, frame, &got_output);
                    if (ret < 0)
                    {
                        fprintf(stderr, "Error encoding frame\n");
                        return EXIT_FAILURE;
                    }
                    if (got_output)
                    {
                        fwrite(pkt.data, 1, pkt.size, f1);
                        av_packet_unref(&pkt);
                    }
                }
                printf("get %d frame success\n", franeCount);

                // 把用完的帧重新插回队列
                if (ioctl(fd, VIDIOC_QBUF, &capture_buf) == -1)
                {
                    printf("insert buf failed %d\n", franeCount);
                    break;
                }
            }
        }

        // 清理资源
        ret = ioctl(fd, VIDIOC_STREAMOFF, &type);
        for (int i = 0; i < CAP_BUF_NUM; i++)
        {
            munmap(buffers[i].start, buffers[i].length);
        }
        free(buffers);
        close(fd);
    }
    return 0;
}