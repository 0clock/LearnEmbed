#include "my_udp.h"

// 服务器端用于通信的套接字，全局变量
struct sockaddr_in server_sin, client_cin;
struct msg_t *user_msg;

enum msg_type_t msg_type;

user userinfo;
linklist userlist;

int sfd;

int udp_init()
{
    // 1、创建套接字
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("sfd = %d\n", sfd);

    // 2、绑定
    // 2.1 填充地址信息结构体

    server_sin.sin_family = AF_INET;
    server_sin.sin_port = htons(SER_PORT);          // 端口号
    server_sin.sin_addr.s_addr = inet_addr(SER_IP); // ip地址

    // 2.2 绑定工作
    if (bind(sfd, (struct sockaddr *)&server_sin, sizeof(server_sin)) == -1)
    {
        perror("bind error");
        return -1;
    }

    return sfd;
}

// 监听
int server_recv()
{
    socklen_t socklen = sizeof(client_cin);

    // bzero(user_msg, sizeof(struct msg_t));

    recvfrom(sfd, (struct msg_t *)user_msg, 1024, 0, (struct sockaddr *)&client_cin, &socklen);

    switch (user_msg->type)
    {
    case LOGIN:
        strcpy(userinfo.username, user_msg->msg);
        userinfo.cin = client_cin;
        userlist = insert_head(userlist, userinfo);
        printf("[%s:%d]%s上线。\n", inet_ntoa(client_cin.sin_addr), ntohs(client_cin.sin_port), user_msg->msg);
        break;
    case CHAT:
        
    default:
        break;
    }
    return 0;
}
