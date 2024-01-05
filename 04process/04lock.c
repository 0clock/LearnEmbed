#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex;
char buf[128];
void * task(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        printf("分支线程中：buf=%s\n",buf);

        strcpy(buf,"I Love Chaina!\n");

        pthread_mutex_unlock(&mutex);

    }
}

int main(int argc, const char *argv[])
{
    pthread_t tid;

    pthread_mutex_init(&mutex,NULL);

    if(pthread_create(&tid,NULL,task,NULL)!=0)
    {
        printf("tid creat error\n");
        return -1;
    }

    while(1)
    {
        pthread_mutex_lock(&mutex);

        printf("主线程中buf=%s\n",buf);
        strcpy(buf,"I Love Chaina!\n");

        pthread_mutex_unlock(&mutex);
    }
    
}