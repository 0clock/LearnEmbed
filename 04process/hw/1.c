/*
 * Filename: 1.c
 * Author: linus
 * Date: 2024-01-05
 * Version: 1.0
 *
 * Description: 互斥机制
 */
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

//创建一个互斥锁
pthread_mutex_t mutex;

void* task(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);

		printf("子线程");

		pthread_mutex_unlock(&mutex);
	}
	

}

int main(int argc, const char *argv[])
{	
	//定义线程号变量
	pthread_t tid;

	//初始化互斥锁
	pthread_mutex_init(&mutex, NULL);

	if(pthread_create(&tid,NULL,task,NULL)!=0)
	{
		perror("tid create error\n");
		return -1;
	}

	while (1)
	{
		//获取锁资源
		pthread_mutex_lock(&mutex);

		printf("主线程\n");

		//释放锁资源
		pthread_mutex_unlock(&mutex);
	}
	



	return 0;
}

