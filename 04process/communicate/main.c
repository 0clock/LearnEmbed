#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

// 创建两个管道文件
int rfd = -1;
int wfd = -1;
int userid = 0;
void *receive(void *arg)
{
    switch (userid)
    {
    case 1:
        if ((rfd = open("./fifo2", O_RDONLY)) == -1)
        {
            perror("open error");
            return NULL;
        }
        break;
    case 2:
        if ((rfd = open("./fifo1", O_RDONLY)) == -1)
        {
            perror("open error");
            return NULL;
        }
        break;
    default:
        break;
    }

    // 以只写的形式打开管道文件

    // 创建有名管道文件
    if (mkfifo("./myfifo", 0664) != 0)
    {
        perror("mkfifo error");
        return NULL;
    }
    // 从管道文件中循环读取数据
    char rbuf[128] = "";
    while (1)
    {
        bzero(rbuf, sizeof(rbuf)); // 清空内容

        // 从管道中读取数据
        read(rfd, rbuf, sizeof(rbuf));

        printf("收到消息：%s\n", rbuf);

        // 判断
        if (strcmp(rbuf, "quit") == 0)
        {
            break;
        }
    }
    pthread_exit(NULL);
}

void *send(void *arg)
{
    switch (userid)
    {
    case 1:
        if ((wfd = open("./fifo1", O_WRONLY)) == -1)
        {
            perror("open error");
            return NULL;
        }
        break;
    case 2:
        if ((wfd = open("./fifo2", O_WRONLY)) == -1)
        {
            perror("open error");
            return NULL;
        }
        break;
    default:
        break;
    }
    printf("登录成功！\n");

    // 以只写的形式打开管道文件

    // 向管道文件中循环写入数据
    char wbuf[128] = "";
    while (1)
    {
        bzero(wbuf, sizeof(wbuf)); // 清空内容
        // 从终端输入数据
        printf("请输入>>>>>");
        fflush(stdout); // 刷新行缓冲区
        read(0, wbuf, sizeof(wbuf));
        wbuf[strlen(wbuf) - 1] = 0; // 将回车换成'\0'

        // 将数据写入管道中
        write(wfd, wbuf, sizeof(wbuf));
        // 判断
        if (strcmp(wbuf, "quit") == 0)
        {
            break ;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    // 创建有名管道文件
    if (mkfifo("./fifo1", 0664) != 0)
    {
        perror("mkfifo error");
        return -1;
    }
    // 创建有名管道文件
    if (mkfifo("./fifo2", 0664) != 0)
    {
        perror("mkfifo error");
        return -1;
    }
    printf("请输入用户ID：");
    scanf("%d", &userid);

    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, receive, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }
    if (pthread_create(&tid2, NULL, send, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    system("rm fifo1");
    system("rm fifo2");

    return 0;
}