/*
 * Filename: 02tcpClint.c
 * Author: linus
 * Date: 2024-01-12
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

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

int main(int argc, const char *argv[])
{
    // 1、创建套接字
    int rfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (rfd == -1)
    {
        perror("sockert error");
        return -1;
    }
    // 2、填充地址信息结构体
    struct sockaddr_in rin;
    rin.sin_family = AF_INET;
    rin.sin_port = htons(6789);
    rin.sin_addr.s_addr = inet_addr("192.168.125.255");

    // 3、绑定
    if (bind(rfd, (struct sockaddr *)&rin, sizeof(rin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    // 4、接受信息
    char rbuf[128] = "";
    while (1)
    {
        bzero(rbuf, sizeof(rbuf));
        recvfrom(rfd, rbuf, sizeof(rbuf), 0, 0, 0);

        printf("收到了新消息：%s\n", rbuf);
    }
    // 5、关闭套接字
    close(rfd);

    return 0;
}