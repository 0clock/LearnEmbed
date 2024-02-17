#include "p_thread.h"
#include "my_udp.h"


pthread_t tid1, tid2;

void *client_recv(void *arg)
{
    struct msg_t * rev_msg=(struct msg_t*)malloc(sizeof(struct msg_t));
    while (1)
    {
        recvfrom(sfd, (struct msg_t *)rev_msg, 1024, 0, (struct sockaddr *)&client_cin, &socklen);
        printf("\r%s:%s\n",rev_msg->username,rev_msg->msg);
        printf(">>>");
        fflush(stdout);
    }
    
}

// 接收消息，并将判断消息类型，做出不同操作
void *ser_receive(void *arg)
{
    while (1)
    {
        server_recv();
    }
    return 0;
}

// 键盘发送给所有用户
void *ser_send(void *arg)
{
    while (1)
    {
        server_send();
    }
    return 0;
}

int thread_init()
{
    if (pthread_create(&tid1, NULL, ser_receive, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }

    if (pthread_create(&tid2, NULL, ser_send, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }
    return 0;
}

int client_thread_init()
{
    if (pthread_create(&tid1, NULL, client_recv, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }
    return 0;
}