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
	int rfd = -1;
	if((rfd = open("./myfifo", O_RDONLY)) == -1)
	{
		perror("open error");
		return -1;
	}
 
	printf("读端打开成功\n");
 
	//从管道文件中循环读取数据
	char rbuf[128] = "";
	while(1)
	{
		// bzero(rbuf, sizeof(rbuf));           //清空内容
 
		// //从管道中读取数据
		// read(rfd, rbuf, sizeof(rbuf));
 
		// printf("收到消息：%s\n", rbuf);
 
		
		// //判断
		// if(strcmp(rbuf, "quit") == 0)
		// {
		// 	break;
		// }
	}
 
	//关闭文件
	close(rfd);
 
	return 0;
}
 