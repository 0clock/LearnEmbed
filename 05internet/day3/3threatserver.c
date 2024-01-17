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
// #include <sys/wait.h>
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

#define SER_PORT 8888                  //服务器端口号
#define SER_IP  "192.168.117.128"      //服务器IP地址
 
//定义一个用于向线程体函数传参的结构体类型
struct MsgInfo
{
	int newfd;
	struct sockaddr_in cin;
};
 
 
//定义线程处理函数
void *deal_cli_msg(void *arg)
{
 
	//解析传进来的参数
	int newfd = ((struct MsgInfo*)arg)->newfd;
	struct sockaddr_in cin = ((struct MsgInfo*)arg)->cin;
 
	//5、跟客户端进行消息通信
	char buf[128] = "";
	while(1)
	{
		//将数组清空
		bzero(buf, sizeof(buf));
 
		//读取客户端发来的消息
		//int res = read(newfd, buf, sizeof(buf));
		int res = recv(newfd, buf, sizeof(buf), 0);
		if(res == 0)
		{
			printf("客户端已经下线\n");
			break;
		}
		printf("[%s:%d] : %s\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), buf);
 
		//给客户端发消息
		strcat(buf, "*_*");
 
		//write(newfd, buf, sizeof(buf));
		send(newfd, buf, sizeof(buf), 0);
		printf("发送成功\n");
	}
 
	//关闭当前通信的套接字
	close(newfd);
 
	//退出线程
	pthread_exit(NULL);
 
 
}
 
 
 
 
int main(int argc, const char *argv[])
{
	//1、创建用于连接的套接字
	int sfd = socket(AF_INET, SOCK_STREAM, 0);  
	//参数1：通信域，表明使用的是ipv4协议
	//参数2：通信方式，使用TCP通信
	//参数3:0表示之前已经指定协议 IPPROTO_TCP
	
	if(sfd == -1)
	{
		perror("socket error");
		return -1;
	}
	printf("sfd = %d\n", sfd);               //3
 
 
	//将端口号快速重用函数
	int reuse = 1;
	if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
	{
		perror("setsockopt error");
		return -1;
	}
	printf("端口号快速重用成功\n");
 
 
 
	//2、给当前套接字绑定IP地址和端口号
	//2.1填充要绑定的地址信息结构体
	struct sockaddr_in sin;
	sin.sin_family = 	AF_INET;        //通信域
	sin.sin_port = 		htons(SER_PORT);  //端口号
	sin.sin_addr.s_addr = 	inet_addr(SER_IP);    //ip地址
 
	//2.2 绑定
	if(bind(sfd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		perror("bind error");
		return -1;
	}
	printf("bind success %s %s %d\n", __FILE__, __func__, __LINE__);
 
	//3、将套接字设置成监听状态
	if(listen(sfd, 128) == -1)
	{
		perror("listen error");
		return -1;
	}
	printf("listen success %s %s %d\n", __FILE__, __func__, __LINE__);
 
	//4、阻塞等待客户端的链接请求
	//4.1定义容器接收客户端的地址信息
	struct sockaddr_in cin;                  //用于接收地址信息
	socklen_t socklen = sizeof(cin);          //用于接收地址信息的大小
 
	int newfd = -1;
 
	pthread_t tid;              //线程id号
 
	while(1)
	{
		//将程序执行到accept处时，系统会给accept函数预选一个文件描述符，按最小未分配原则
		//即使后期可能会有更小的文件描述符，在本次操作时，不会选择
 
		//4.2 接收客户端的链接
		newfd = accept(sfd, (struct sockaddr*)&cin, &socklen);   
		if(newfd == -1)
		{
			perror("accept error");
			return -1;
		}
		printf("[%s:%d:%d]发来链接请求 %s %s %d\n", \
				inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), newfd, __FILE__, __func__, __LINE__);
 
		//定义用于传参的结构体变量
		struct MsgInfo info;
		info.newfd = newfd;
		info.cin = cin;
 
 
		//创建分支线程，用于跟新连接的客户端进行交互
		if(pthread_create(&tid, NULL, deal_cli_msg, &info) != 0)
		{
			printf("分支线程创建失败\n");
			return -1;
		}
 
		//回收线程资源
		//pthread_join(tid, NULL);
		pthread_detach(tid);             //将线程分离，后期退出后，由系统回收资源
 
	}
 
	//6、关闭套接字
	close(sfd);
 
 
 
 
 
	return 0;
}
 