#include "header.h"
#include "loger.h"
#include "my_udp.h"

#define CLI_PORT 9999
#define CLI_IP "192.168.117.128"

int main(int argc, const char *argv[])
{
    user_msg=(struct msg_t*)malloc(sizeof(struct msg_t));
    // 1、创建套接字
    int cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("cfd = %d\n", cfd);
    printf("用户名>>>");
    user_msg->type = LOGIN;
    scanf("%s",user_msg->msg);
    
    
    //3、填充服务器的地址信息结构体
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SER_PORT);
	sin.sin_addr.s_addr = inet_addr(SER_IP);

    sendto(cfd, user_msg, sizeof(struct msg_t), 0, (struct sockaddr *)&sin,sizeof(sin));


    while (1)
    {
        ;
    }
    
    return 0;
}
