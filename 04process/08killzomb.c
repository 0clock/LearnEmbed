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

void hander(int signum)
{
    if(signal(SIGCHLD,hander) == SIG_ERR)
    {
        while(waitpid(-1,NULL,WNOHANG)>0);
    }
}