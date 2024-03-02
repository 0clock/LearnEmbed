#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <netinet/in.h> // 提供了 Internet 地址族相关的数据结构和函数，如 sockaddr_in 结构体等
#include <sys/socket.h> // 提供了套接字编程相关的系统调用和数据结构，如 socket、bind、listen 等
#include <arpa/inet.h>  // 提供了 IP 地址转换函数，如 inet_addr 和 inet_ntoa

#include <stdlib.h> // 标准库头文件，提供了内存分配、随机数生成等功能
#include <string.h> // 标准库头文件，提供了字符串处理函数，如 strcpy 和 strlen

#define PORT 8888

#endif