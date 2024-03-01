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

using namespace cv;

int main() {
    // 初始化摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        fprintf(stderr, "Error: Unable to open camera.\n");
        return -1;
    }

    // 创建服务器套接字
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建 TCP 套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    //将端口号快速重用函数
	int reuse = 1;
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
	{
		perror("setsockopt error");
		return -1;
	}
	printf("端口号快速重用成功\n");


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    

    // 绑定套接字到端口
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 开始监听连接
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for incoming connections...\n");

    // 接受连接请求
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

    // 缓冲区用于存储图像数据
    uchar buffer[BUFFER_SIZE];

    // 主循环，持续发送图像数据
    while (1) {
        Mat frame;
        cap >> frame; // 从摄像头读取图像数据

        // 调整图像大小以适应传输
        resize(frame, frame, Size(WIDTH, HEIGHT));

        // 将图像数据转换为字节流
        memcpy(buffer, frame.data, BUFFER_SIZE);

        // 发送图像数据给客户端
        if (send(client_fd, buffer, BUFFER_SIZE, 0) != BUFFER_SIZE) {
            perror("send failed");
            break;
        }
        printf("send success\n");

        // 为了控制帧率，添加适当的延迟
        usleep(100000); // 1000 毫秒
    }

    // 关闭连接
    close(client_fd);
    close(server_fd);

    return 0;
}
