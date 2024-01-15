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

int cfd;
struct sockaddr_in cin;
char send_buf[5];

int RobArmCtl(char buf[128])
{
    static int x = 0, y = 0;

    switch (buf[0])
    {
    case 'W':
        x++;
        send_buf[2] = 0x00;
        send_buf[3] = x;
        break;
    case 'S':
        send_buf[2] = 0x00;
        send_buf[3] = x;
        x--;
        break;
    case 'A':
        y++;
        send_buf[2] = 0x01;
        send_buf[3] = y;
        break;
    case 'D':
        y--;
        send_buf[2] = 0x01;
        send_buf[3] = y;
        break;
    default:
        break;
    }

    send_buf[0] = 0xff;
    send_buf[1] = 0x02;

    send_buf[4] = 0xff;
    write(cfd, send_buf, sizeof(send_buf));
}

int init()
{
    send_buf[0] = 0xff;
    send_buf[1] = 0x02;
    send_buf[2] = 0x00;
    send_buf[3] = 0x00;
    send_buf[4] = 0xff;
    write(cfd, send_buf, sizeof(send_buf));

    send_buf[0] = 0xff;
    send_buf[1] = 0x02;
    send_buf[2] = 0x01;
    send_buf[3] = 90;
    send_buf[4] = 0xff;
    write(cfd, send_buf, sizeof(send_buf));
}

int main(int argc, const char *argv[])
{
    // 创建套接字
    cfd = socket(AF_INET, SOCK_STREAM, 0);

    cin.sin_family = AF_INET;
    cin.sin_port = htons(8888);
    cin.sin_addr.s_addr = inet_addr("192.168.117.1");

    // 连接服务器
    connect(cfd, (struct sockaddr *)&cin, sizeof(cin));
    init();

    char buf[128] = "";
    while (1)
    {
        printf("请输入指令：");
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        RobArmCtl(buf);
        printf("指令发送成功\n");
    }

    return 0;
}
