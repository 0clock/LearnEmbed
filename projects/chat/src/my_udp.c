#include "my_udp.h"

// 服务器端用于通信的套接字，全局变量
struct sockaddr_in server_sin, client_cin;
struct msg_t *user_msg;
socklen_t socklen = sizeof(client_cin);

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

// 将消息转发给其他用户
int send_usermsg_to_other(user userinfo, struct msg_t *user_msg, linklist userlist)
{
    linklist temp = userlist;
    while (temp != NULL)
    {

        if (0 != (strcmp(user_msg->username, temp->data.username)))
        {
            sendto(sfd, user_msg, sizeof(struct msg_t), 0, (struct sockaddr *)&temp->data.cin, sizeof(temp->data.cin));
        }
        temp = temp->next;
    }
    return 0;
}

// 将消息转发给其他用户
int send_broadcast(struct msg_t *broadcas, linklist userlist)
{
    linklist temp = userlist;
    while (temp != NULL)
    {
        sendto(sfd, broadcas, sizeof(struct msg_t), 0, (struct sockaddr *)&temp->data.cin, sizeof(temp->data.cin));
        temp = temp->next;
    }
    return 0;
}

// 监听
int server_recv()
{
    // bzero(user_msg, sizeof(struct msg_t));

    recvfrom(sfd, (struct msg_t *)user_msg, 1024, 0, (struct sockaddr *)&client_cin, &socklen);

    switch (user_msg->type)
    {
    case LOGIN:
        strcpy(userinfo.username, user_msg->username);
        userinfo.cin = client_cin;
        userlist = insert_head(userlist, userinfo);
        printf("[%s:%d]%s上线。\n", inet_ntoa(userinfo.cin.sin_addr), ntohs(userinfo.cin.sin_port), userinfo.username);
        break;
    case CHAT:
        strcpy(userinfo.username, user_msg->username);
        userinfo.cin = client_cin;
        send_usermsg_to_other(userinfo, user_msg, userlist);
        user_msg->type = QUIT;
        break;
    case QUIT:
        strcpy(userinfo.username, user_msg->username);
        userinfo.cin = client_cin;
        userlist = insert_head(userlist, userinfo);
        printf("[%s:%d]%s下线。\n", inet_ntoa(userinfo.cin.sin_addr), ntohs(userinfo.cin.sin_port), userinfo.username);
        break;
    default:
        break;
    }
    return 0;
}

int server_send()
{
    struct msg_t * broadcas=(struct msg_t *)malloc(sizeof(struct msg_t));
    broadcas->type = BOCST;
    strcpy(broadcas->username, "ADMIN");
    scanf("%s", broadcas->msg);
    send_broadcast(broadcas, userlist);
    return 0;
}
