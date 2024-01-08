#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

pthread_cond_t cond;

pthread_mutex_t mutex;

size_t sailcount=0;

void *task1(void *arg)
{
    size_t count=0;
    while (1)
    {
        count++;
        printf("\n%#lx:一共生产了%ld辆特斯拉\n", pthread_self(),count);
        pthread_cond_signal(&cond);
        // sleep(1);
    }
}

void *task2(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        //会在这阻塞
        pthread_cond_wait(&cond, &mutex);

        pthread_mutex_unlock(&mutex);

        printf("%#lx:一共消费了%ld辆特斯拉\n", pthread_self(),++sailcount);
    }

    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    pthread_cond_init(&cond, NULL);

    pthread_mutex_init(&mutex, NULL);

    pthread_t tid1, tid2, tid3, tid4, tid5;

    if (pthread_create(&tid1, NULL, task1, NULL) != 0)
    {
        printf("生产者创建失败\n");
        return -1;
    }

    if (pthread_create(&tid2, NULL, task2, NULL) != 0)
    {
        printf("消费者创建失败\n");
        return -1;
    }
    if (pthread_create(&tid3, NULL, task2, NULL) != 0)
    {
        printf("消费者创建失败\n");
        return -1;
    }
    if (pthread_create(&tid4, NULL, task2, NULL) != 0)
    {
        printf("消费者创建失败\n");
        return -1;
    }
    if (pthread_create(&tid5, NULL, task2, NULL) != 0)
    {
        printf("消费者创建失败\n");
        return -1;
    }

    printf("tid1=%#lx\ntid2=%#lx\ntid3=%#lx\ntid4=%#lx\ntid5=%#lx\n",
           tid1, tid2, tid3, tid4, tid5);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}