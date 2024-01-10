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
#include <sys/shm.h>
#include <errno.h>

#include"sem.h"
#define PAGE_SIZE 4096
int main(int argc, const char *argv[])
{
 
	//11、创建并初始化一个信号灯集
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
 
		//22、申请0号灯的资源
		sem_wait(semid, 0);
 
		fgets(addr, PAGE_SIZE, stdin);   //从终端输入数据
		addr[strlen(addr) - 1] = '\0';    //将换行换成'\0'
 
		//33、释放1号灯的资源
		sem_post(semid, 1);
 
		if(strcmp(addr, "quit") == 0)
		{
			break;
		}
 
	}
 
	
	//5、取消映射
 
	while(1);
 
	return 0;
}