/*
 * Filename: 2.c
 * Author: linus
 * Date: 2024-01-05
 * Version: 1.0
 *
 * Description: The purpose of this code.
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

sem_t sem;

void* task1(void* arg)
{
	while(1)
	{
		sem_post(&sem);
		printf("post了sem\n");
		sleep(2);
	}
	pthread_exit(NULL);
}

void* task2(void* arg)
{
	while(1)
	{
		sem_wait(&sem);
		printf("收到了\n");

	}

	pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
	pthread_t tid1,tid2;

	sem_init(&sem,0,0);

	if((pthread_create(&tid1,NULL,task1,NULL))!=0)
	{
		perror("thread creat error");
		return -1;
	}
	if((pthread_create(&tid2,NULL,task2,NULL))!=0)
	{
		perror("thread creat error");
		return -1;
	}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}