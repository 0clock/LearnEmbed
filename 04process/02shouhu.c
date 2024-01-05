#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>


int main(int argc, const char *argv[])
{
    pid_t pid=fork();
    if(pid==0)
    {
        setsid();

        chdir("/");

        umask(0);

        int fd=-1;
        if((fd=open("log.txt",O_RDWR|O_CREAT|O_APPEND))==-1)
        {
            perror("open error");
            return -1;
        }

        dup2(fd,0);
        dup2(fd,1);
        dup2(fd,2);

        int i=0;

        while (1)
        {
            printf("[%d]-Hello World!\n",i);
            fflush(stdout);
            sleep(2);
        }
        

    }
    else if(pid<0)
    {
        perror("fork error");
        return -1;
    }
    exit(EXIT_SUCCESS);
}