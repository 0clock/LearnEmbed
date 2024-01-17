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
    // 1、创建套接字
    int sfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sfd ==-1)
    {
        perror("socket error");
        return -1;
    }
    // 2、将套接字设置成允许广播
    int broadcast = 1;
    if(setsockopt(sfd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast))==-1)
    {
        perror("setsocketopt error");
        return -1;
    }
    // 3、绑定（非必须）
    // 4、填充接收端地址信息结构体
    struct sockaddr_in cin;
    cin.sin_family = AF_INET;
    cin.sin_port=htons(6789);
    cin.sin_addr.s_addr = inet_addr("192.168.125.255");

    // 5、发送消息
    char sbuf[128]="";
    while (1)
    {
        printf(">>>");
        fgets(sbuf,sizeof(sbuf),stdin);
        sbuf[strlen(sbuf)-1]=0;

        sendto(sfd,sbuf,sizeof(sbuf),)
    }
    



    return 0;
}