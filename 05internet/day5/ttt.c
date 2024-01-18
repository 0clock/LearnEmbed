#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#define SER_PORT 69
#define SER_IP "192.168.117.1"

int main(int argc, const char *argv[])
{
    int log_fp = -1;
    log_fp = open("./log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (log_fp == -1)
    {
        perror("创建文件失败:");
        return -1;
    }

    // 1、创建用于通信的套接字文件描述符
    int cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }

    // 输入文件名
    printf("请输入要拷贝的文件名：");
    char filename[128];
    fgets(filename, sizeof(filename), stdin);
    filename[strlen(filename) - 1] = '\0';

    // 创建文件
    int fd_cp = -1;
    fd_cp = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);

    if (fd_cp == -1)
    {
        perror("创建文件失败:");
        return -1;
    }

    // 2、绑定（可选）
    // 3、填充服务器的地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SER_PORT);
    sin.sin_addr.s_addr = inet_addr(SER_IP);

    // 向服务器发送下载请求

    // 发送下载请求
    char buf[516] = "";
    int size = sprintf(buf, "%c%c%s%c%s%c", 0, 1, filename, 0, "octet", 0);

    // char send_buf[516] = "";

    // // 组装请求数据
    // short *p1 = (short *)send_buf;
    // *p1 = htons(1);

    // char *p2 = send_buf + 2;
    // strcpy(p2, &filename[0]);
    // char *p3 = p2 + strlen(p2) + 1;
    // strcpy(p3, "octet");
    // int len = 4 + strlen(p2) + strlen(p3); // 要发送的长度
    // // 向服务器发送请求
    sendto(cfd, buf, size, 0, (struct sockaddr *)&sin, sizeof(sin));
    char rbuf[1024] = "";
    int res = 0;
    short *block_count = (short *)(buf + 2);

    char log_buf[1024] = "";

    short num = 1;

    socklen_t addrlen = sizeof(sin);

    while (1) // res == 512
    {
        bzero(buf, 516);
        res = recvfrom(cfd, buf, sizeof(rbuf),0,(struct sockaddr *)&sin,&addrlen);
        if (res < 0)
		{
            perror("recvfrom");
			return -1;
		}

        printf("res=%d\n", res);

        if (ntohs(*((short *)buf)) == 5)
        {
            printf("ERROR:\n");
            printf("[ERROR_CODE]:%d\n", ntohs(*((short *)(buf + 2))));
            printf("[ERROR_MSG]:%s\n", buf + 4);
            break;
        }
        else if (ntohs(*((short *)buf)) == 3)
        {
            printf("收到了数据包\n");
            // write(fd_cp, rbuf + 4, res - 4);
            if (num == ntohs(*((short *)(buf + 2))))
            {
                buf[1] = 4;
                // 返回ACK
                if (sendto(cfd, buf, 4, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
                {
                    perror("sendto error:");
                    return -1;
                }
                write(log_fp, buf, 4);
                printf("返回了ACK\n");
            }

            printf("block_count=%d\n", ntohs(*block_count));
        }

        // if (res < 516)
        // {
        //     printf("-----文件下载完毕!!-----\n");
        //     break;
        // }
    }

    // //5、关闭套接字
    close(cfd);
    close(fd_cp);
    return 0;
}