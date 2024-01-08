/*
 * Filename: 4.c
 * Author: linus
 * Date: 2024-01-05
 * Version: 1.0
 *
 * Description: 使用三个线程完成：线程1输出字符’A’,线程2输出字符’B’,
 *				线程3输出字符’C’,
 *				要求输出结果为：
 *				ABCABCABCABCABC…
 *				思路：使用三个互斥信号量来实现排队输出
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
#include <semaphore.h>

sem_t sem1,sem2,sem3;

void* task1(void *arg)
{
	while (1)
	{
		sem_wait(&sem2);
		printf("B");
		fflush(stdout);//遇到的坑，没有刷新缓存区
		sem_post(&sem3);
	}
}

void* task2(void *arg)
{
	while (1)
	{
		sem_wait(&sem3);
		printf("C");
		fflush(stdout);
		sem_post(&sem1);
	}
}

int main(int argc, const char *argv[])
{
	// 初始化匿名信号量
	sem_init(&sem1,0,1);
	sem_init(&sem2,0,0);
	sem_init(&sem2,0,0);
	// 创建两个线程
	pthread_t tid1, tid2;
	
	if ((pthread_create(&tid1, NULL, task1, NULL)) != 0)
	{
		perror("thread creat error");
		return -1;
	}
	if ((pthread_create(&tid2, NULL, task2, NULL)) != 0)
	{
		perror("thread creat error");
		return -1;
	}
	printf("线程创建成功\n");
	
	// 主线程
	
	while (1)
	{
		sem_wait(&sem1);
		printf("A");
		fflush(stdout);
		sem_post(&sem2);
		// sleep(1);
	}
	// 释放线程
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}
