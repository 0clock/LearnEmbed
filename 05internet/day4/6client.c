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
	int cfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(cfd == -1)
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
 
 
    //2、绑定
    //2.1 填充地址信息结构体
    struct sockaddr_un cun;
    cun.sun_family = AF_UNIX;
    strcpy(cun.sun_path, "./unix");
 
    //2.2 绑定工作
    if(bind(cfd, (struct sockaddr*)&cun, sizeof(cun)) == -1)                       
    {   
        perror("bind error");
        return -1;
    }   
  
	//3、填充服务器的地址信息结构体
	struct sockaddr_un sun;
	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, "./linux");
 
 
	//4、数据收发
	char buf[128] = "";
	while(1)
	{
		printf("请输入>>>");
		fgets(buf, sizeof(buf), stdin);
		buf[strlen(buf)-1] = '\0';
 
		//发送给服务器
		sendto(cfd, buf, sizeof(buf), 0, (struct sockaddr*)&sun, sizeof(sun));
 
		if(strcmp(buf, "quit") == 0)
		{
			break;
		}
 
		//接收服务器发送来的消息
		recvfrom(cfd, buf, sizeof(buf), 0, NULL, NULL);
		printf("收到消息：%s\n", buf);
 
 
	}
 
	//5、关闭套接字
	close(cfd);
 
 
	return 0;
}
 