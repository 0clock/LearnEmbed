#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* task(void *arg)
{   
    //拒接退出
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);


    printf("我是分支线程：tid=%#lx\n",pthread_self());

    sleep(5);

    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    pthread_t tid=0;

    if(pthread_create(&tid,NULL,task,NULL)!=0)
    {
        printf("tid creat error\n");
        return -1;
    }

    printf("tid creat success tid = %#lx\n",tid);

    sleep(2);

    pthread_detach(tid);
    printf("已设成分离态\n");

    //向分支线程发送一个取消请求
    pthread_cancel(tid);

    sleep(8);
    printf("此时分支线程已经退出了\n");
    return 0;
}