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

//定义信号处理函数
void handler(int signum)
{
	if(signum == SIGINT)      //表明要处理2号信号
	{
		printf("用户按下了ctrl + c键\n");
	}
 
	if(signum == SIGQUIT)          //处理暂停信号
	{
 
		printf("用户按下了ctrl + z键\n");
	}
 
 
	if(signum == SIGSTOP)          //处理暂停信号
	{
 
		printf("用户按下了ctrl + z键\n");
	}
}
 
/****************************主程序********************/
int main(int argc, const char *argv[])
{
	// 尝试忽略SIGSTOP信号
	if(signal(SIGINT, handler) == SIG_ERR)
	{
		perror("signal error");
		return -1;
	}
	
 
	// // 尝试捕获SIGSTOP信号
	if(signal(SIGQUIT, handler) == SIG_ERR)
	{
		perror("signal error");
		return -1;
	}
	
 
	//尝试默认处理SIGSTOP信号
	// if(signal(SIGSTOP, SIG_DFL) == SIG_ERR)
	// {
	// 	perror("signal error");
	// 	return -1;
	// }
 
	while(1)
	{
		sleep(1);
		printf("我真的还想再活五百年\n");
	}
 
	return 0;
}
 