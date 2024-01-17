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
	//1、创建用于通信的套接字文件描述符
	int cfd = -1;
	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(cfd == -1)
	{
		perror("socket error");
		return -1;
	}
	printf("cfd = %d\n", cfd);            //3
 
    //由于域套接字的绑定函数，只能绑定一个不存在的套接字文件
    //所以，在绑定之前需要判断当前文件是否存在
    if(access("./linux", F_OK) == 0)
    {   
        //表示文件存在,删除该文件
        if(unlink("./linux")==-1)
        {
            perror("unlink error");
            return -1; 
        }
    }   
 
 
 
 
	//2、绑定（可选）如果客户端不绑定套接字文件，则系统不会自动绑定套接字文件
	//2.1 填充地址信息结构体
	struct sockaddr_un cun;
	cun.sun_family = AF_UNIX;
	strcpy(cun.sun_path,"./linux");
 
	//2.2绑定
	if(bind(cfd, (struct sockaddr*)&cun, sizeof(cun)) == -1)
	{
		perror("bind error");
		return  -1;
	}
	printf("bind  success\n");
 
	
	//3、连接服务器
	//3.1 填充服务器地址信息结构体
	struct sockaddr_un sun;
	sun.sun_family = 	AF_UNIX;
	strcpy(sun.sun_path, "./unix");     //要使用套接字文件进行通信
 
	//3.2 连接
	if(connect(cfd, (struct sockaddr*)&sun, sizeof(sun)) == -1)
	{
		perror("connect error");
		return -1;
	}
	printf("connect success\n");
	
 
	//4、收发数据
	char buf[128] = "";
	while(1)
	{
		//清空数组
		bzero(buf, sizeof(buf));
 
		printf("请输入>>>");
		fgets(buf, sizeof(buf), stdin);   //从终端输入数据
		buf[strlen(buf)-1] = 0;          //将换行改为'\0'
 
		//发送给服务器
		send(cfd, buf, sizeof(buf), 0);
		printf("发送成功\n");
		if(strcmp(buf, "quit") == 0)
		{
			break;
		} 
	}
 
	//5、关闭套接字
	close(cfd);
 
	return 0;
}
 