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
#include <sys/un.h>

int main(int argc, const char *argv[])
{
	//1、创建套接字
	int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	//int sfd = socket(AF_UNIX, SOCK_RAW, IPPROTO_TCP);
	if(sfd == -1)
	{
		perror("socket error");
		return -1;
	}
 
 
	//由于域套接字的绑定函数，只能绑定一个不存在的套接字文件
	//所以，在绑定之前需要判断当前文件是否存在
	if(access("./unix", F_OK) == 0)
	{
		//表示文件存在,删除该文件
		if(unlink("./unix")==-1)
		{
			perror("unlink error");
			return -1;
		}
	}
 
	//2、填充地址信息结构体
	struct sockaddr_un sun;
	sun.sun_family = AF_UNIX;        //通信域
	//sun.sun_path = ".unix";            //字符串赋值不能使用赋值运算符
	strcpy(sun.sun_path, "./unix");      //绑定套接字文件
 
	//3、绑定地址信息结构体
	if(bind(sfd, (struct sockaddr*)&sun, sizeof(sun)) == -1)
	{
		perror("bind error");
		return -1;
	}
	printf("bind success\n");
 
	//4、监听
	if(listen(sfd, 128) ==-1)
	{
		perror("listen error");
		return -1;
	}
 
	//5、阻塞接收客户端链接请求
	//定义容器接收客户端地址信息结构体
	struct sockaddr_un cun;
	socklen_t socklen = sizeof(cun);
 
	int newfd = accept(sfd, (struct sockaddr*)&cun, &socklen);    //表示不接收客户端地址信息
	if(newfd == -1)
	{
		perror("accept error");
		return -1;
	}
 
	//6、收发数据
	char buf[128] = "";
	while(1)
	{
		//清空数组
		bzero(buf, sizeof(buf));
 
		int res = recv(newfd, buf, sizeof(buf), 0);       //读取消息
		if(res == 0)
		{
			printf("客户端已经下线\n");
			break;
		}
		printf("[%s]: %s\n", cun.sun_path ,buf);
 
	}
 
	//7、关闭套接字
	close(newfd);
	close(sfd);
 
 
	return 0;
}
 