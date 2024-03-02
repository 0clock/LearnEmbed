#include "network.hpp"

int NetWork::init()
{
    client_len = sizeof(client_addr);
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
    printf("网络初始化完成\n");

    return 0;
}

int NetWork::wait()
{
    // 缓冲区用于存储图像数据
    char recbuf[4] = "";
    recvfrom(server_fd, recbuf, sizeof(recbuf), 0, (struct sockaddr *)&client_addr, &client_len);
    return 0;
}

int NetWork::send_img(vector<uchar> *jpeg_buffer)
{
    ssize_t bytes_sent = sendto(server_fd, jpeg_buffer->data(), jpeg_buffer->size(), 0, (struct sockaddr *)&client_addr, client_len);
    if (bytes_sent != jpeg_buffer->size())
    {
        perror("sendto failed");
    }
    return 0;
}
