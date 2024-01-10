#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
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
#include <errno.h>
#include <sys/shm.h>

#include"sem.h"
#define PAGE_SIZE 4096 
int main(int argc, const char *argv[])
{
 
	//11、创建信号灯集
	int semid = sem_creat(2);
 
 
	//1、创建key值
	key_t key = -1;
	if((key = ftok("/", 't')) == -1)
	{
		perror("ftok error");
		return -1;
	}
	printf("key = %#x\n", key);
 
	//2、将物理内存创建出共享内存段
	int shmid = 0;
	if((shmid = shmget(key, PAGE_SIZE, IPC_CREAT|0664)) == -1)
	{
		perror("shmget error");
		return -1;
	}
	printf("shmid = %d\n", shmid);
 
	//3、将共享内存段地址映射到用户空间
	//NULL表示让系统自动选择页的分段
	//0表示当前进程对共享内存具有读写功能
	char *addr = (char *)shmat(shmid, NULL, 0);
	if(addr == (void *)-1)
	{
		perror("shmat error");
		return -1;
	}
	printf("addr = %p\n", addr);
	
	//4、操作共享内存
	//char buf[128] = "";
	while(1)
	{
		//22、申请1号灯的资源
		sem_wait(semid, 1);
	
		printf("共享内存中的数据为：%s\n", addr);
 
 
		//33、释放0号灯的资源
		sem_post(semid, 0);
 
		if(strcmp(addr, "quit") == 0)
		{
			break;
		}
 
	}
 
	
	//5、取消映射
	if(shmdt(addr) == -1)
	{
		perror("shmdt error");
		return -1;
	}
 

	//6、删除共享内存
	if(shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("shmctl error");
		return -1;
	}
 
	//44、删除信号灯集
	delete_sem(semid);
 
	return 0;
}
