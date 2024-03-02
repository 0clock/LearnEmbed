#include "camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
    // 停止捕捉并清理资源
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1) {
        perror("ioctl");
    }

    for (int i = 0; i < req.count; ++i) {
        munmap(buffers[i].start, buffers[i].length);
    }
    free(buffers);

    close(fd);
}

int Camera::cam_init()
{
    struct v4l2_format fmt;         // V4L2 格式结构体，用于设置视频格式

    // 打开摄像头设备
    fd = open("/dev/video0", O_RDWR);
    if (fd == -1)
    {
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
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
    {
        perror("ioctl");
        return -1;
    }

    // 分配缓冲区
    memset(&req, 0, sizeof(req));
    req.count = BUFFER_COUNT;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1)
    {
        perror("ioctl");
        return -1;
    }

    // 映射缓冲区
    buffers = (struct buffer *)calloc(req.count, sizeof(*buffers));
    for (int i = 0; i < req.count; ++i)
    {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
        {
            perror("ioctl");
            return -1;
        }

        buffers[i].length = buf.length;
        buffers[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if (buffers[i].start == MAP_FAILED)
        {
            perror("mmap");
            return -1;
        }
    }

    // 启动捕捉
    for (int i = 0; i < req.count; ++i)
    {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
        {
            perror("ioctl");
            return -1;
        }
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) == -1)
    {
        perror("ioctl");
        return -1;
    }

    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(IMAGE_QUALITY);
}

int Camera::get_fram()
{
    Mat frame;
    // 从摄像头中取出帧
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1)
    {
        perror("ioctl");
        return -1;
    }

    // 处理图像数据（这里只是简单地使用OpenCV展示）
    frame = cv::Mat(HEIGHT, WIDTH, CV_8UC2, buffers[buf.index].start);
    cvtColor(frame, frame, COLOR_YUV2BGR_YUYV); // 转换为BGR格式
    // cv::imshow("Frame", frame);
    // cv::waitKey(1);

    addTimestampWatermark(frame);

    imencode(".jpg", frame, jpeg_buffer, params);
    // 将帧重新放入缓冲区队列
    if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
    {
        perror("ioctl");
        return -1;
    }
}

void Camera::addTimestampWatermark(Mat &image)
{
    // 获取当前时间
    time_t rawTime;
    struct tm *timeInfo;
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