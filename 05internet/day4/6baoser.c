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
#include <sys/un.h>

int main(int argc, const char *argv[])
{
    // 1、创建套接字
    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    // SOCK_DGRAM:表示使用UDP报式套接字通信
    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("sfd = %d\n", sfd);

    // 由于域套接字的绑定函数，只能绑定一个不存在的套接字文件
    // 所以，在绑定之前需要判断当前文件是否存在
    if (access("./linux", F_OK) == 0)
    {
        // 表示文件存在,删除该文件
        if (unlink("./linux") == -1)
        {
            perror("unlink error");
            return -1;
        }
    }

    // 2、绑定
    // 2.1 填充地址信息结构体
    struct sockaddr_un sun;
    sun.sun_family = AF_UNIX;
    strcpy(sun.sun_path, "./linux");

    // 2.2 绑定工作
    if (bind(sfd, (struct sockaddr *)&sun, sizeof(sun)) == -1)
    {
        perror("bind error");
        return -1;
    }

    // 3、数据收发
    char buf[128] = "";
    // 定义变量存放客户端地址信息结构体
    struct sockaddr_un cun;
    socklen_t socklen = sizeof(cun);

    while (1)
    {
        // 清空数组
        bzero(buf, sizeof(buf));

        // 从套接字文件中读取消息
        recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&cun, &socklen);

        printf("[%s]：%s\n", cun.sun_path, buf);

        // 将字符串连接后回发
        strcat(buf, "*_*");
        // if(write(sfd, buf, sizeof(buf)) == -1)
        if (sendto(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&cun, sizeof(cun)) == -1)
        {
            perror("write error");
            return -1;
        }
        printf("发送成功\n");
    }

    // 4、关闭套接字
    close(sfd);

    return 0;
}
