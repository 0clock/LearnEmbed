#include "header.h"
#include "linklist.h"
#include "loger.h"

// 服务器端口号和IP
#define SER_PORT 8888
#define SER_IP "192.168.117.128"

int main(int argc, const char *argv[])
{
    // 1、创建要用于连接的套接字
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET:通信域，表示使用的是IPV4协议
    // 参数二：通信方式，表示的使用TCP通信
    // 参数三：0表示之前已经指定协议 IPPROYO_TCP

    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }

    int reuse = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        perror("setsockopt error");
        return -1;
    }
    // 2、给当前套接字绑定IP和端口号
    struct sockaddr_in sin;
    sin.sin_family = AF_INET; // 通信域
    sin.sin_port = htons(SER_PORT);
    sin.sin_addr.s_addr = inet_addr(SER_IP);

    // 2.2、绑定
    if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    // 3、将套接字设置成监听状态
    if (listen(sfd, 128) == -1)
    {
        perror("listen error");
        return -1;
    }

    // 4、阻塞客户端的连接请求
    // 4.1、定义容器接收客户端的地址信息
    struct sockaddr_in cin;
    socklen_t socklen = sizeof(cin);

    int newfd = -1;

    fd_set readfds, tempfds;

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(sfd, &readfds);

    int maxfd = sfd;

    user user;

    struct sockaddr_in cin_arr[1024];

    while (1)
    {
        tempfds = readfds;
        int res = select(maxfd + 1, &tempfds, NULL, NULL, NULL);
        if (res == -1)
        {
            perror("select error");
            return -1;
        }
        else if (res == 0)
        {
            printf("timeout\n");
            // return -1;
        }

        // 判断是否是文件描述符触发事件
        for (int cli = 0; cli <= maxfd; cli++)
        {
            if (!FD_ISSET(cli, &tempfds))
                continue;

            // 有新客户端连接
            if (cli == sfd)
            {
                newfd = accept(sfd, (struct sockaddr *)&cin, &socklen);
                if (newfd == -1)
                {
                    perror("accept error");
                    return -1;
                }

                printf("[%s:%d]已连接\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port));
                // user.cin=cin;
                cin_arr[newfd] = cin;

                FD_SET(newfd, &readfds);
                if (newfd > maxfd)
                {
                    maxfd = newfd;
                }
            }
            else
            {
                if (cli == 0)
                {
                    char wbuf[128] = "";
                    scanf("%s", wbuf);
                    printf("触发了终端输入事件。。。\n");
                    if (strcmp(wbuf, "quit") == 0)
                        goto END;

                    for (int i = 4; i <= maxfd; i++)
                    {
                        sendto(i, wbuf, sizeof(wbuf), 0, (struct sockaddr *)&cin_arr[i], sizeof(cin_arr[i]));
                    }
                }
                else
                {
                    char buf[128] = "";
                    bzero(buf, sizeof(buf));

                    int res = recv(cli, buf, sizeof(buf), 0);
                    if (res == 0)
                    {
                        printf("客户端下线\n");
                        close(cli);
                        FD_CLR(cli, &readfds);
                        for (int i = maxfd; i >= sfd; i--)
                        {
                            if (FD_ISSET(i, &readfds))
                            {
                                maxfd = i;
                                break;
                            }
                        }
                        continue;
                    }
                    printf("[%s:%d]:%s\n", inet_ntoa(cin_arr[cli].sin_addr), ntohs(cin_arr[cli].sin_port), buf);

                    strcat(buf, "* V *");
                    send(cli, buf, sizeof(buf), 0);
                    printf("发送成功\n");
                }
            }
        }
    }
END:
    close(sfd);
    return 0;
}
