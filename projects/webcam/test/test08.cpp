#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <opencv2/opencv.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>

#define PORT 8888

#define WIDTH 640
#define HEIGHT 480
#define BUFFER_COUNT 4
#define IMAGE_QUALITY 80              // JPEG压缩质量

#define BUFFER_SIZE WIDTH *HEIGHT * 3 // RGB图像数据大小 921600
#define DATA_SIZE 1024                // RGB图像数据大小
#define PACKET_SIZE 1024              // 每个数据包的大小
#define LEN  (WIDTH*HEIGHT*2)
struct buffer {
    void *start;
    size_t length;
};

using namespace cv;
using namespace std;

void addTimestampWatermark(Mat& image) {
    // 获取当前时间
    time_t rawTime;
    struct tm* timeInfo;
    char buffer[80];
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
    std::string timestamp(buffer);

    // 在图像上添加时间水印
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 2.2;
    int baseline = 0;
    Size textSize = getTextSize(timestamp, fontFace, fontScale, thickness, &baseline);
    Point textOrg(image.cols - textSize.width - 10, image.rows - 10);
    putText(image, timestamp, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness);
}

int main() {
    int fd;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers req;
    struct v4l2_format fmt;
    struct buffer *buffers;

    // 打开摄像头设备
    fd = open("/dev/video0", O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    // 设置视频格式
    memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = WIDTH;
    fmt.fmt.pix.height = HEIGHT;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; // 修改为您摄像头支持的格式
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
        perror("ioctl");
        return -1;
    }

    // 分配缓冲区
    memset(&req, 0, sizeof(req));
    req.count = BUFFER_COUNT;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
        perror("ioctl");
        return -1;
    }

    // 映射缓冲区
    buffers = (struct buffer*)calloc(req.count, sizeof(*buffers));
    for (int i = 0; i < req.count; ++i) {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1) {
            perror("ioctl");
            return -1;
        }

        buffers[i].length = buf.length;
        buffers[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if (buffers[i].start == MAP_FAILED) {
            perror("mmap");
            return -1;
        }
    }

    // 启动捕捉
    for (int i = 0; i < req.count; ++i) {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
            perror("ioctl");
            return -1;
        }
    }
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) == -1) {
        perror("ioctl");
        return -1;
    }

    // 创建服务器套接字
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建 UDP 套接字
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定套接字到端口
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for incoming connections...\n");

    // 缓冲区用于存储图像数据
    uchar buffer[BUFFER_SIZE];
    char recbuf[4] = "";

    recvfrom(server_fd, recbuf, sizeof(recbuf), 0, (struct sockaddr *)&client_addr, &client_len);


    // 编码参数
    vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(IMAGE_QUALITY);

    // 循环捕捉并处理帧
    Mat frame;
    for (;;) {
        // 从摄像头中取出帧
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) {
            perror("ioctl");
            return -1;
        }
        
        // 处理图像数据（这里只是简单地使用OpenCV展示）
        frame = cv::Mat(HEIGHT, WIDTH, CV_8UC2, buffers[buf.index].start);
        cvtColor(frame, frame, COLOR_YUV2BGR_YUYV); // 转换为BGR格式
        // cv::imshow("Frame", frame);
        // cv::waitKey(1);
        vector<uchar> jpeg_buffer;

        addTimestampWatermark(frame);

        imencode(".jpg", frame, jpeg_buffer, params);

        //保存成jpg文件，可行
        if (0)
        {
            FILE *fp = fopen("./new.jpg", "w");
            if (NULL == fp) // 说明文件打开失败
            {
                printf("open file error\n");
                return -1;
            }
            fwrite(jpeg_buffer.data(), jpeg_buffer.size(), 1, fp);
            fclose(fp);
        }

        if(1)
        {
            ssize_t bytes_sent = sendto(server_fd, jpeg_buffer.data(), jpeg_buffer.size(), 0, (struct sockaddr *)&client_addr, client_len);
            if (bytes_sent != jpeg_buffer.size())
                {
                    perror("sendto failed");
                    break;
                }
                // printf("send success,size=%ld\n",jpeg_buffer.size());
            // usleep(50000); // 50毫秒
        }

        // 将帧重新放入缓冲区队列
        if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
            perror("ioctl");
            return -1;
        }
    }

    // 停止捕捉并清理资源
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1) {
        perror("ioctl");
        return -1;
    }

    for (int i = 0; i < req.count; ++i) {
        munmap(buffers[i].start, buffers[i].length);
    }
    free(buffers);

    close(fd);

    return 0;
}
