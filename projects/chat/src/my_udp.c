#include "my_udp.h"

struct sockaddr_in server_sin;


int udp_init()
{
    // 1、创建套接字
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("sfd = %d\n", sfd);

    //2、绑定
	//2.1 填充地址信息结构体
	
	server_sin.sin_family = AF_INET;
	server_sin.sin_port = htons(SER_PORT);       //端口号
	server_sin.sin_addr.s_addr = inet_addr(SER_IP);  //ip地址
    // 2.2 绑定工作
    if (bind(sfd, (struct sockaddr *)&server_sin, sizeof(server_sin)) == -1)
    {
        perror("bind error");
        return -1;
    }

    return sfd;
}

