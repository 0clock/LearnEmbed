#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <linux/videodev2.h>     // Linux 视频设备驱动 API
#include <opencv2/opencv.hpp>    // OpenCV 主要头文件，提供计算机视觉和图像处理功能
#include <opencv2/objdetect.hpp> // OpenCV 对象检测功能头文件，包括人脸检测等
#include <opencv2/imgproc.hpp>   // OpenCV 图像处理功能头文件，包括图像滤波、边缘检测等
#include <opencv2/face.hpp>      // OpenCV 人脸识别和表情识别功能头文件
#include <fcntl.h>               // 提供对文件控制的功能，如打开文件、设置文件状态标志等
#include <iostream>              // 标准输入输出流，用于控制台输入输出
#include <sys/ioctl.h>           // 提供对设备的输入输出控制功能
#include <sys/mman.h>            // 提供内存映射相关的函数和宏定义
#include <stdio.h>               // 标准输入输出头文件，提供了常见的输入输出函数，如 printf 和 scanf
#include <ctime>                 // C++ 标准库中的时间处理头文件，提供了日期和时间的功能，如获取当前时间等
#include <stdlib.h>              // 标准库头文件，提供了内存分配、随机数生成等功能
#include <string.h>              // 标准库头文件，提供了字符串处理函数，如 strcpy 和 strlen
#include <unistd.h>              // 提供了对 POSIX 系统调用的封装，如 close、fork、pipe 等

using namespace cv;
using namespace std;

#define WIDTH 640
#define HEIGHT 480
#define BUFFER_COUNT 4
#define IMAGE_QUALITY 80 // JPEG压缩质量
class CameraImageProcess
{

public:
    CameraImageProcess();
    int cam_init();
    int get_fram();
    void addTimestampWatermark(Mat &image);
    void save_image();

    vector<uchar> *jpeg_buffer; // 处理完可以发送的图像数据

private:
    int fd;                 // 操作相机的句柄
    struct v4l2_buffer buf; // V4L2（Video4Linux2）缓冲区结构体，用于管理视频缓冲区
    vector<int> params;     // 编码参数
    struct buffer
    {
        void *start;
        size_t length;
    };
    struct buffer *buffers; // 自定义的缓冲区结构体指针，用于管理视频数据缓冲区
    enum v4l2_buf_type type;
    struct v4l2_requestbuffers req; // V4L2 请求缓冲区结构体，用于请求视频缓冲区
};

#endif //_CAMERA_HPP_