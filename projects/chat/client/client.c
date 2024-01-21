#include "header.h"
#include "loger.h"
#include "my_udp.h"
#include "p_thread.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <wchar.h>
#define CLI_PORT 9999
#define CLI_IP "192.168.117.128"

int getTerminalWidth()
{
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

// 判断字符是否是中文字符
int isChineseChar(const char *str)
{
    unsigned char c = (unsigned char)(*str);

    // UTF-8中，中文字符的第一个字节的最高两位是11
    // 也就是二进制的110xxxxx，这里检查第一个字节是否符合这个规律
    return (c & 0xC0) == 0xC0;
}

void right_print(char *text)
{
    int textLength = strlen(text);
    // 将光标定位到行尾
    // printf("\033[1;80H");
    printf("\n\b");
    for (int i = 0; i < textLength; i++)
    {
        // 使用 ANSI 转义序列将光标前移一个字符
        printf("\b");
        printf("%c", *(text + i));
    }
}

void printRightAligned(char *text, int totalWidth)
{
    int textLength = strlen(text);
    int padding = totalWidth - textLength;

    // 输出前面的空格
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }

    // 输出文本
    printf("%s\n", text);
}

int main(int argc, const char *argv[])
{
    user_msg = (struct msg_t *)malloc(sizeof(struct msg_t));
    // 1、创建套接字
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("sfd = %d\n", sfd);
    printf("用户名>>>");
    user_msg->type = LOGIN;
    scanf("%s", user_msg->username);

    // 3、填充服务器的地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SER_PORT);
    sin.sin_addr.s_addr = inet_addr(SER_IP);

    sendto(sfd, user_msg, sizeof(struct msg_t), 0, (struct sockaddr *)&sin, sizeof(sin));

    // 接收消息的线程
    client_thread_init();

    user_msg->type = CHAT;

    while (1)
    {
        printf(">>>");
        scanf("%s", user_msg->msg);
        // char show_sendmsg[2048] = "";
        printf("\033[1A"); // 光标上移一行
        printf("\033[K");  // 清除光标所在行
        printf("\033[1;34m%s:%s\n\033[0m",user_msg->username,user_msg->msg);
        // sprintf(show_sendmsg, "%s:%s\n\a", user_msg->msg, user_msg->username);
        // printRightAligned(show_sendmsg, getTerminalWidth());

        if (strcmp(user_msg->msg, "quit") == 0)
        {
            user_msg->type = QUIT;
        }

        sendto(sfd, user_msg, sizeof(struct msg_t), 0, (struct sockaddr *)&sin, sizeof(sin));

        if (user_msg->type == QUIT)
        {
            break;
        }
    }

    // 6、关闭套接字
    close(sfd);
    return 0;
}
