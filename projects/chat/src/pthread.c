#include "p_thread.h"


pthread_t tid1, tid2;

void *ser_receive(void *arg)
{
    printf("hi");
    return 0;
}

void *ser_send(void *arg)
{
    printf("hi");
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