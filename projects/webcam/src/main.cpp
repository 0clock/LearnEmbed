#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>

#define PORT 8888
#define WIDTH 640
#define HEIGHT 480
#define BUFFER_SIZE WIDTH * HEIGHT * 3 // RGB图像数据大小
#define FRAM_SIZE WIDTH * HEIGHT * 3 // RGB图像数据大小
#define PACKET_SIZE 1024 // 每个数据包的大小

using namespace cv;

enum MsgState{
    Firstpak,
    
    LasePak
};

typedef struct MagPack_T{
    MsgState state;
    char Data[]
} MsgPack;

int SendFram(const struct sockaddr * cfd,socklen_t client_len)
{

}

int main() {
    // 初始化摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        fprintf(stderr, "Error: Unable to open camera.\n");
        return -1;
    }

    // 创建服务器套接字
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建 UDP 套接字
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定套接字到端口
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for incoming connections...\n");

    // 缓冲区用于存储图像数据
    uchar buffer[BUFFER_SIZE];

    char buf[4] = {0x00,0x00,0x99};
    
    recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &client_len);

    // 主循环，持续发送图像数据
    while (1) {
        recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &client_len);
        Mat frame;
        cap >> frame; // 从摄像头读取图像数据

        // 调整图像大小以适应传输
        resize(frame, frame, Size(WIDTH, HEIGHT));
        
        sendto(server_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, client_len);

        // 将图像数据分割成数据包并发送给客户端
        int total_packets = (BUFFER_SIZE + PACKET_SIZE - 1) / PACKET_SIZE; // 计算总的数据包数
        for (int i = 0; i < total_packets; ++i) {
            int offset = i * PACKET_SIZE;
            int packet_size = std::min(BUFFER_SIZE - offset, PACKET_SIZE);
            memcpy(buffer, frame.data + offset, packet_size);

            // 发送图像数据给客户端
            ssize_t bytes_sent = sendto(server_fd, buffer, packet_size, 0, (struct sockaddr *)&client_addr, client_len);
            if (bytes_sent != packet_size) {
                perror("sendto failed");
                break;
            }
            printf("send success: packet %d/%d\n", i + 1, total_packets);

            // 为了控制帧率，添加适当的延迟
            usleep(100); // 10 毫秒
        }
    }
    // 关闭套接字
    close(server_fd);

    return 0;
}
