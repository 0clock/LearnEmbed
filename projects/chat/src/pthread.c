#include "p_thread.h"
#include "my_udp.h"


pthread_t tid1, tid2;


// 接收消息，并将判断消息类型，做出不同操作
void *ser_receive(void *arg)
{
    while(1)
    {
        server_recv();

    }
    return 0;
}

// 键盘发送给所有用户
void *ser_send(void *arg)
{
    while(1)
    {

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