#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
 
#define ERR_LOG(msg) do{\
	perror(msg);\
	printf("%d %s %s\n", __LINE__, __func__, __FILE__);\
}while(0)
 
 
#define PORT 	69
#define N 		516
 
int do_download(int , struct sockaddr_in );
int do_upload(int sfd, struct sockaddr_in sin);
 
 
int main(int argc, const char *argv[])
{
	if(argc < 2)
	{
		printf("请输入IP\n");
		return -1;
	}
	//1.创建报式套接字
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd < 0)
	{
		perror("socket");
		return -1;
	}
 
	//2.填充服务器ip和端口号
	struct sockaddr_in sin;
	sin.sin_family 		= AF_INET;
	sin.sin_port 		= htons(PORT);
	sin.sin_addr.s_addr = inet_addr(argv[1]);
 
 
	char choose;
	while(1)
	{
		system("clear");
		printf("******************\n");
		printf("******1.下载******\n");
		printf("******2.上传******\n");
		printf("******3.退出******\n");
		printf("******************\n");
 
		scanf("%c", &choose);
		while(getchar()!=10);
 
		switch(choose)
		{
		case '1':
			//下载功能, todo
			do_download(sfd, sin);
			break;
		case '2':
			//上传功能,todo
			do_upload(sfd, sin);
			break;
		case '3':
			goto END;
			break;
		default:
			printf("输入错误\n");
		}
		printf("请输入任意字符清屏>>>");
		while(getchar()!=10);		
	}
	
	//关闭文件描述符
END:
	close(sfd);
	return 0;
}
 
 
//上传功能
int do_upload(int sfd, struct sockaddr_in sin)
{
	char filename[20] = "";
	printf("请输入要上传的文件名>>>");
	fgets(filename, 20, stdin);
	filename[strlen(filename)-1] = 0;
 
	//判断该文件是否存在
	int fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		if(errno == ENOENT)
		{
			printf(">>>文件不存在,请重新输入<<<\n");
			return -2;
		}
		else
		{
			ERR_LOG("open");
			return -1;
		}
	}
	
	//发送上传请求
	//上传协议
	char buf[N] = "";
	int size = sprintf(buf, "%c%c%s%c%s%c", 0, 2, filename, 0, "octet", 0);
 
	if(sendto(sfd, buf, size, 0, (struct sockaddr*)&sin, sizeof(sin))<0)
	{
		ERR_LOG("sendto");
		return -1;
	}
 
	//循环接收发送数据包
	int recv_len;
	unsigned short num = 0;
	socklen_t addrlen = sizeof(sin);
	while(1)
	{
		bzero(buf, N);
		recv_len = recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr*)&sin, &addrlen);
		if(recv_len < 0)
		{
			ERR_LOG("recvfrom");
			return -1;
		}
 
		//操作码的范围是1-5,因为是网络字节序
		//所以有效操作吗存储在高位,即buf[1]的位置.
		//printf("buf[1] = %d\n", buf[1]); 	//4 服务器返回应答包
		if(4 == buf[1])
		{
			//判断当前数据包的编号是否等于应答包的编号
			//防止数据包在传送过程丢包或重复收包
			if(num == ntohs(*(unsigned short*)(buf+2)))
			{
				//修改操作码为数据包
				buf[1] = 3;
 
				//填充块编号
				num++;
				*(unsigned short*)(buf+2) = htons(num);
 
				//读取数据
				//发送数据
				int res = read(fd, buf+4, N-4);
				if(res < 0)
				{
					ERR_LOG("read");
					return -1;
				}
				else if(0 == res)
				{
					printf("-----文件上传完毕-----\n");
					break;
				}
 
				//发送数据包
				//发送的数据包大小为,读取到的字节数(res)+操作码(2byte)+快编号(2byte)
				if(sendto(sfd, buf, res+4, 0, (struct sockaddr*)&sin, sizeof(sin)) <0)
				{
					ERR_LOG("sendto");
					return -1;
				}
			}
			else
			{
				printf("-----文件上传失败,请检查网络环境-----\n");
				break;
			}
		}
		else if(5 == buf[1])
		{
			printf("-----ERROR:%s-----\n", buf+4);
			break;
		}
 
	}
	return 0;
}
 
 
//下载功能
int do_download(int sfd, struct sockaddr_in sin)
{
	char filename[20] = "";
	printf("请输入要下载的文件名>>>");
	fgets(filename, 20, stdin);
	filename[strlen(filename)-1] = 0;
 
	//发送下载请求
	char buf[N] = "";
	int size = sprintf(buf, "%c%c%s%c%s%c", 0, 1, filename, 0, "octet", 0);
 
	if(sendto(sfd, buf, size, 0, (struct sockaddr*)&sin, sizeof(sin))<0)
	{
		ERR_LOG("sendto");
		return -1;
	}
 
	int flag = 0;
	int fd ;
 
	//循环接收发送应答包
	ssize_t recv_len;
	unsigned short num = 1;
	socklen_t addrlen = sizeof(sin);
	while(1)
	{
		bzero(buf, N);
		recv_len = recvfrom(sfd, buf, N, 0, (struct sockaddr*)&sin, &addrlen);
		if(recv_len < 0)
		{
			ERR_LOG("recvfrom");
			return -1;
		}
		if(3 == buf[1]) 			//如果是数据包
		{
			if(0 == flag) 	//防止文件重复打开
			{
				//存储从服务器下载下来的文件,接收数据成功后再创建数据；
				//创建并打开filename文件
				fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0664);
				if(fd < 0)
				{
					ERR_LOG("open");
					return -1;
				}
				flag = 1;
			}
			//判断当前的快编号，是否与我期望的快编号一致
			if(htons(num) == *(unsigned short*)(buf+2)) 	//防止数据包重复到达
			{
				//提取数据，写入到文件中
				//char str[513] = "";
				//strncpy(str, buf+4, 512);
				//printf("%s", str);
				//fflush(stdout);
 
				if(write(fd, buf+4, recv_len-4) < 0)
				{
					printf("fd:%d recv_len=%ld\n", fd, recv_len);
					ERR_LOG("write");
					break;
				}
 
				//回复ack包
				//由于数据包前四个字节与ack包除了操作码不一致外，其余全部一致。
				//所以我们直接将数据包的操作码修改成4即可，发送数据包的前四个字节。
				buf[1] = 4; 	
				if(sendto(sfd, buf, 4, 0, (struct sockaddr*)&sin, sizeof(sin)) < 0)
				{
					ERR_LOG("sendto");
				}
 
				//判断数据包的大小是否小于 512+2+2;
				if(recv_len < 512+2+2)
				{
					printf("-----文件下载完毕!!-----\n");
					break;
				}
				num++;
			}
		}
		else if(5 == buf[1]) 	//错误包
		{
			//打印错误信息
			printf("-----ERROR:%s-----\n", buf+4);
			break;
		}
	}
	return 0;
}
 