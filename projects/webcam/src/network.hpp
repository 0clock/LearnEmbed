#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <vector>
#include <stdio.h>      // 标准输入输出头文件，提供了常见的输入输出函数，如 printf 和 scanf
#include <netinet/in.h> // 提供了 Internet 地址族相关的数据结构和函数，如 sockaddr_in 结构体等
#include <sys/socket.h> // 提供了套接字编程相关的系统调用和数据结构，如 socket、bind、listen 等
#include <arpa/inet.h>  // 提供了 IP 地址转换函数，如 inet_addr 和 inet_ntoa
#include <stdlib.h>     // 标准库头文件，提供了内存分配、随机数生成等功能
#include <string.h>     // 标准库头文件，提供了字符串处理函数，如 strcpy 和 strlen
#include <unistd.h>     // 提供了对 POSIX 系统调用的封装，如 close、fork、pipe 等

#include <opencv2/core.hpp> // 如果使用 OpenCV，包含头文件以获得 uchar 类型
#define PORT 8888

using namespace std;

class NetWork
{
public:
    int init();
    int wait();
    int send_img(vector<uchar> *jpeg_buffer);

private:
    // 创建服务器套接字
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len ;
};

#endif