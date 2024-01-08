#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	//以只写的形式打开管道文件
	int wfd = -1;
	//创建有名管道文件
	if(mkfifo("./myfifo", 0664) != 0)
	{
		perror("mkfifo error");
		return -1;
	}
 
	printf("myfifo create success\n");

	if((wfd = open("./myfifo", O_WRONLY)) == -1)
	{
		perror("open error");
		return -1;
	}
 
	printf("写端打开成功\n");
 
	//向管道文件中循环写入数据
	char wbuf[128] = "";
	while(1)
	{
		bzero(wbuf, sizeof(wbuf));           //清空内容
 
		//从终端输入数据
		printf("请输入>>>>>");
		fflush(stdout);            //刷新行缓冲区
		read(0, wbuf, sizeof(wbuf));
		wbuf[strlen(wbuf)-1] = 0;           //将回车换成'\0'
 
		//将数据写入管道中
		write(wfd, wbuf, sizeof(wbuf));
 
		//判断
		if(strcmp(wbuf, "quit") == 0)
		{
			
			system("rm myfifo");
			break;
		}
	}
 
	//关闭文件
	close(wfd);
 
	return 0;
}