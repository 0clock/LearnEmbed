#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <poll.h>

#define SER_PORT 8888            // 服务器端口号
#define SER_IP "192.168.117.128" // 服务器客户端

int main(int argc, const char *argv[])
{
    // 1、创建用于连接的套接字
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    // 参数1：通信域，表明使用的是ipv4协议
    // 参数2：通信方式，使用TCP通信
    // 参数3:0表示之前已经指定协议 IPPROTO_TCP

    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("sfd = %d\n", sfd); // 3

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    if (setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
    {
        perror("setsockopt error");
        return -1;
    }

    // 将端口号快速重用函数
    int reuse = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        perror("setsockopt error");
        return -1;
    }
    printf("端口号快速重用成功\n");

    // 2、给当前套接字绑定IP地址和端口号
    // 2.1填充要绑定的地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;                // 通信域
    sin.sin_port = htons(SER_PORT);          // 端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP); // ip地址

    // 2.2 绑定
    if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success %s %s %d\n", __FILE__, __func__, __LINE__);

    // 3、将套接字设置成监听状态
    if (listen(sfd, 128) == -1)
    {
        perror("listen error");
        return -1;
    }
    printf("listen success %s %s %d\n", __FILE__, __func__, __LINE__);

    // 4、阻塞等待客户端的链接请求
    // 4.1定义容器接收客户端的地址信息
    struct sockaddr_in cin;          // 用于接收地址信息
    socklen_t socklen = sizeof(cin); // 用于接收地址信息的大小

    int newfd = -1;
    // 4.2 接收客户端的链接
    newfd = accept(sfd, (struct sockaddr *)&cin, &socklen);
    if (newfd == -1)
    {
        perror("accept error");
        return -1;
    }
    printf("[%s:%d]发来链接请求 %s %s %d\n",
           inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), __FILE__, __func__, __LINE__);

    // 5、跟客户端进行消息通信
    char buf[128] = "";
    while (1)
    {
        // 将数组清空
        bzero(buf, sizeof(buf));

        // 读取客户端发来的消息
        // int res = read(newfd, buf, sizeof(buf));
        int res = recv(newfd, buf, sizeof(buf), 0);
        if (res == 0)
        {
            printf("客户端已经下线\n");
            break;
        }
        printf("[%s:%d] : %s\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), buf);

        // 给客户端发消息
        strcat(buf, "*_*");

        // write(newfd, buf, sizeof(buf));
        send(newfd, buf, sizeof(buf), 0);
        printf("发送成功\n");
    }

    // 6、关闭套接字
    close(newfd);
    close(sfd);

    return 0;
}
