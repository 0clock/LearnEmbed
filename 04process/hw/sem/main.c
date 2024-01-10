// 使用信号灯集完成三个进程的同步，
// A进程输出字符A，B进程输出字符B，C进程输出字符C，
// 要求输出结果为ABCABCABCABCABC...
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "sem.h"

int main(int argc, const char *argv[])
{
    int semid = sem_creat(3);

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // 子进程1
        int count = 10000;
        while (count--)
        {
            sem_wait(semid, 0);
            printf("A");
            fflush(stdout);
            sem_post(semid, 1);
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid1 == -1)
    {
        perror("fork error");
        return -1;
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        // 子进程2
        int count = 10000;
        while (count--)
        {
            sem_wait(semid, 1);
            printf("B");
            fflush(stdout);
            sem_post(semid, 2);
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid2 == -1)
    {
        perror("fork error");
        return -1;
    }

    pid_t pid3 = fork();
    if (pid3 == 0)
    {
        // 子进程3
        int count = 10000;
        while (count--)
        {
            sem_wait(semid, 2);
            printf("C");
            fflush(stdout);
            sem_post(semid, 0);
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid3 == -1)
    {
        perror("fork error");
        return -1;
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    delete_sem(semid);

    return 0;
}
