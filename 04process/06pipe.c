#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

int main(int argc, const char *argv[])
{
    // 定义进程号变量
    pid_t pid;

    // 创建一个无名管道
    int pipefd[2];
    if (pipe(pipefd) != 0)
    {
        perror("pipe error");
        return -1;
    }

    printf("pipefd[0]=%d, pipefd[1]=%d\n", pipefd[0], pipefd[1]); // 3,4

    // 创建子进程
    pid = fork();

    if (pid > 0)
    {
        close(pipefd[0]);
        while (1)
        {   // 父进程,拥有管道文件的两个文件描述符
            char buf[128] = "";
            read(stdin->_fileno,buf,sizeof(buf));
            buf[strlen(buf)-1]='\0';
            // 将数据写入到管道文件中
            write(pipefd[1], buf, sizeof(buf));
            // 关闭写段
            close(pipefd[1]);
        }
    }
    else if (pid == 0)
    {
        while (1)
        { // 子进程，也有用管道文件的两个文件描述符
            
            // 从管道文件中读取数据
            char rbuf[128] = "";

            read(pipefd[0], rbuf, sizeof(rbuf));
            printf("子进程中收到：%s\n", rbuf);
            close(pipefd[1]);

        }

        // 退出子进程
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("fork error");
        return -1;
    }

    wait(NULL); // 回收子进程资源

    return 0;
}