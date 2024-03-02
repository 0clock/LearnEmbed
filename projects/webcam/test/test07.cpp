#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>
#include <ctime>

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>


#define PORT 8888
#define WIDTH 640
#define HEIGHT 480
#define BUFFER_SIZE WIDTH *HEIGHT * 3 // RGB图像数据大小 921600
#define DATA_SIZE 1024                // RGB图像数据大小
#define PACKET_SIZE 1024              // 每个数据包的大小
#define IMAGE_QUALITY 80              // JPEG压缩质量
#define LEN  (WIDTH*HEIGHT*2)


using namespace cv;
using namespace std;

enum TransStatus{
    TS_IDLE,       //空闲(图像数据可以更新)
    TS_RUNNING,    //图像数据传输中(还不可以更新图像数据)
    TS_FIRST_DATA, //需要发出图像数据的第一部分
};


class ImgData {
public:
    char data[LEN] = {0}; //图像数据
    int  totalLen = 0; //图像大小
    int  hasSentLen = 0; //已发出的数据长度
    TransStatus  stats = TS_IDLE; //工作状态
};


enum MsgState
{
    Firstpak,

    LasePak
};

typedef struct MagPack_T
{
    char data[DATA_SIZE];
    char totalpack;
    // MsgState state;
    // char Data[]
} MsgPack;

// int SendFram(const struct sockaddr * cfd,socklen_t client_len)
// {
// ;
// }

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
    double fontScale = 1.5;
    int thickness = 2.2;
    int baseline = 0;
    Size textSize = getTextSize(timestamp, fontFace, fontScale, thickness, &baseline);
    Point textOrg(image.cols - textSize.width - 10, image.rows - 10);
    putText(image, timestamp, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness);
}

// 函数用于在帧中检测人脸
void detectFaces(cv::Mat& frame, cv::CascadeClassifier& faceCascade) {
    std::vector<cv::Rect> faces;
    cv::Mat grayFrame;

    // 将帧转换为灰度图
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    // 在灰度帧中检测人脸
    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 4);

    // 在检测到的人脸周围绘制矩形框
    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    }
}

int main()
{
    // 初始化摄像头
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        fprintf(stderr, "Error: Unable to open camera.\n");
        return -1;
    }

    // 设置摄像头参数
    // cap.set(cv::CAP_PROP_BACKEND, cv::CAP_V4L);
    cap.set(CAP_PROP_FRAME_WIDTH, 640);  // 设置帧宽度
    cap.set(CAP_PROP_FRAME_HEIGHT, 480); // 设置帧高度
    cap.set(CAP_PROP_FPS, 30);             // 设置帧率

    // 检查参数是否被正确设置
    double width = cap.get(CAP_PROP_FRAME_WIDTH);
    double height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "Frame width: " << width << ", Frame height: " << height << ", FPS: " << fps << std::endl;


    // 初始化人脸级联分类器
    CascadeClassifier faceCascade;
    if (!faceCascade.load(samples::findFile("./haarcascade_frontalface_alt2.xml"))) {
        fprintf(stderr, "错误：无法加载人脸级联分类器。\n");
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
    char buf[4] = "";

    recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);

    MsgPack sendbuf;
    printf("sizeof(sendbuf) = %ld\n", sizeof(sendbuf));

    // 编码参数
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(IMAGE_QUALITY);

    // 主循环，持续发送图像数据
    Mat frame;
    int count = 0;
    while (1)
    {
        count ++;
        // recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);

        cap >> frame; // 从摄像头读取图像数据

        // 在帧中检测人脸
        // detectFaces(frame, faceCascade);//比较卡

        addTimestampWatermark(frame);
        // 调整图像大小以适应传输
        resize(frame, frame, Size(WIDTH, HEIGHT));

        vector<uchar> jpeg_buffer;

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
        //发送原始数据，太慢了，且卡
        if (0)
        {
            sendbuf.totalpack = 0;
            // 将图像数据分割成数据包并发送给客户端
            int total_packets = (BUFFER_SIZE + PACKET_SIZE - 1) / PACKET_SIZE; // 计算总的数据包数
            for (int i = 0; i < total_packets; ++i)
            {
                int offset = i * PACKET_SIZE;
                int packet_size = std::min(BUFFER_SIZE - offset, PACKET_SIZE);
                memcpy(sendbuf.data, frame.data + offset, packet_size);

                // 发送图像数据给客户端
                ssize_t bytes_sent = sendto(server_fd, &sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&client_addr, client_len);
                if (bytes_sent != sizeof(sendbuf))
                {
                    perror("sendto failed");
                    break;
                }
                printf("send success: packet %d/%d\n", i + 1, total_packets);

                sendbuf.totalpack = 1;
                usleep(10000);

                // 为了控制帧率，添加适当的延迟
                if (waitKey(100) == 27) // 按ESC键退出
                    break;
            }
        }
    }
    // 关闭套接字
    close(server_fd);

    return 0;
}
