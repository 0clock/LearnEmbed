/*
 * Filename: 3.c
 * Author: linus
 * Date: 2024-01-05
 * Version: 1.0
 *
 * Description: 使用三个线程完成两个文件的拷贝，
 * 				线程1完成拷贝前一半，线程2完成拷贝后一半，
 * 				主线程回收两个分支线程的资源
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
int len,half_hen;
const char *srcFile,*destFile;

int file_len(const char *file)
{
	FILE* fp=NULL;
	if((fp=(fopen(file,"r")))==NULL)
	{
		perror("open fire error");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	return ftell(fp);
}

int copy_file(const char *srcFile, const char *destFile, int begin, int end)
{
	FILE* srcfp=NULL;
	FILE* destfp=NULL;
	if ((srcfp=(fopen(srcFile, "r"))) == NULL)
	{
		perror("open srcFile error");
		return -1;
	}
	if ((destfp=(fopen(destFile, "w"))) == NULL)
	{
		perror("open destFile error");
		return -1;
	}

	fseek(destfp,begin,SEEK_SET);
	fseek(srcfp,begin,SEEK_SET);
	char buff;
	while(ftell(srcfp)<end)
	{
		int res=fread(&buff,1,sizeof(buff),srcfp);	
		fwrite(&buff,1,res,destfp);
	}
	fclose(srcfp);
	fclose(destfp);
	return 0;
}

void *task1(void *arg)
{
	copy_file(srcFile,destFile,0,half_hen);
	pthread_exit(NULL);
}

void *task2(void *arg)
{
	copy_file(srcFile,destFile,half_hen,len);
	pthread_exit(NULL);

}

int main(int argc, const char *argv[])
{
	if(argc!=3)
	{
		printf("输入有误！\n");
		return -1;
	}
	

	srcFile=argv[1];
	destFile=argv[2];

	len=file_len(argv[1]);
	half_hen=len/2;
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


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}