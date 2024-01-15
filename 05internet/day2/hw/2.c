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

#define SER_PORT 8888           // 服务器端口号
#define SER_IP "192.168.117.128" // 服务器ip地址
#define CLI_PORT 6666           // 客户端的端口号
#define CLI_IP "192.168.117.128" // 客户端ip地址
int cfd;
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
    send(cfd, send_buf, sizeof(send_buf), 0);
}

int init()
{
    send_buf[0] = 0xff;
    send_buf[1] = 0x02;
    send_buf[2] = 0x00;
    send_buf[3] = 0x00;
    send_buf[4] = 0xff;
    send(cfd, send_buf, sizeof(send_buf), 0);

    send_buf[0] = 0xff;
    send_buf[1] = 0x02;
    send_buf[2] = 0x01;
    send_buf[3] = 90;
    send_buf[4] = 0xff;
    send(cfd, send_buf, sizeof(send_buf), 0);
}

int main(int argc, const char *argv[])
{
    // 1、创建用于通信的套接字文件描述符
    int cfd = -1;
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("cfd = %d\n", cfd); // 3

    // // 2、绑定（可选）
    // // 2.1 填充地址信息结构体
    // struct sockaddr_in cin;
    // cin.sin_family = AF_INET;
    // cin.sin_port = htons(CLI_PORT);
    // cin.sin_addr.s_addr = inet_addr(CLI_IP);
    // // 2.2绑定
    // if (bind(cfd, (struct sockaddr *)&cin, sizeof(cin)) == -1)
    // {
    //     perror("bind error");
    //     return -1;
    // }
    // printf("bind  success\n");

    // 3、连接服务器
    // 3.1 填充服务器地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SER_PORT);
    sin.sin_addr.s_addr = inet_addr(SER_IP);
    // 3.2 连接
    if (connect(cfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("connect error");
        return -1;
    }
    printf("connect success\n");
    init();

    // 4、收发数据
    char buf[128] = "";
    while (1)
    {
        // 清空数组
        bzero(buf, sizeof(buf));

        printf("请输入>>>");
        fgets(buf, sizeof(buf), stdin); // 从终端输入数据
        buf[strlen(buf) - 1] = 0;       // 将换行改为'\0'

        // 发送给服务器
        RobArmCtl(buf);
        send(cfd, "Hello", sizeof("Hello"), 0);
        printf("发送成功\n");
        if (strcmp(buf, "quit") == 0)
        {
            break;
        }

        // 接收服务器发来的消息
        // recv(cfd, buf, sizeof(buf), 0);
        // printf("[%s:%d]:%s\n", SER_IP, SER_PORT, buf);
    }

    // 5、关闭套接字
    close(cfd);

    return 0;
}
