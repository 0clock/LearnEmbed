/*
 * Filename: 02tcpClint.c
 * Author: linus
 * Date: 2024-01-12
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include <stdio.h>
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, const char *argv[])
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1)
    {
        perror("socket error");
        return -1;
    }

    int reuse = -1;
    int reuse_size = sizeof(reuse);
    if(getsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,&reuse_size)==-1)
    {
        perror("getsockeropt error");
        return -1;
    }

    printf("reuse = %d\n",reuse);

    reuse=1;
    if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))==-1)
    {
        perror("setsockopt error");
        return -1;
    }

    printf("端口号快速重用成功\n");

    reuse = -1;
    if(getsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,&reuse_size)==-1)
    {
        perror("getsockeropt error");
        return -1;
    }

    printf("reuse = %d\n",reuse);

    return 0;
}
 