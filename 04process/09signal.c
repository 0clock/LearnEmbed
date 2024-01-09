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
void hander(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("逆子！\n");
        raise(SIGKILL);
    }
}

int main(int argc, const char *argv[])
{
    pid_t pid = fork;
    if (pid > 0)
    {
        if (signal(SIGUSR1, hander) == SIG_ERR)
        {
            perror("signal error");
            return -1;
        }

        while (1)
        {
            printf("我还想再活500年\n");
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        printf("人生得意需尽欢，莫使金杯空对月\n");
        sleep(3);

        printf("我看透了红尘， 父亲跟我一起走吧\n");

        // 向父进程发送一个信号
        kill(getppid(), SIGUSR1);

        exit(EXIT_SUCCESS); // 退出进程
    }
    else
    {
        perror("fork error");
        return -1;
    }
    return 0;
}