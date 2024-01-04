#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	//定义文件描述符变量
	int fd = -1;
 
	//以只写的形式打开文件
	if((fd = open("./test.txt", O_WRONLY|O_CREAT|O_TRUNC, 0664)) ==-1)
	{
		perror("open error");
		return -1;
	}
	printf("fd = %d\n", fd);             //3
 
	char buf[128] = "hello world ni hao I love China\n";
	//将字符串写入到文件
	int res = write(fd, buf, strlen(buf));
	printf("res = %d\n", res);                //
 
	//关闭文件
	close(fd);
 
	//以只读的形式打开文件
	if((fd = open("./test.txt", O_RDONLY)) ==-1)
	{
		perror("open error");
		return -1;
	}
	printf("fd = %d\n", fd);             //3
 
	char rbuf[128] = "";
	res = read(fd, rbuf, sizeof(rbuf));
	printf("res = %d\n", res);                //?
	write(stdout->_fileno, rbuf, res);
 
	//关闭文件
	close(fd);
 
 
 
 
	return 0;
}
 