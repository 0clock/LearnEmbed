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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
    long mtype;
    char mtext[1024];
};
#define SIZE (sizeof(struct msgbuf) - sizeof(long))

int main(int argc, const char *argv[])
{
	//1、创建key值
	key_t key = 0;
	if((key = ftok("/", 't')) == -1)
	{
		perror("fork error");
		return -1;
	}
 
	printf("key = %#x\n", key);
 
	//2、使用key值创建一个消息队列
	int msqid = 0;
	if((msqid=msgget(key, IPC_CREAT|0664)) == -1)
	{
		perror("msgget error");
		return -1;
	}
 
	printf("msqid = %d\n", msqid);
 
	//此时就已经在内核空间创建出消息队列了
	//定义一个消息类型的容器
	struct msgbuf buf = {.mtype=100};
 
	//3、循环向消息队列中存放数据
	while(1)
	{
		printf("请输入要存放的数据:");
		scanf("%s", buf.mtext);
		getchar();                   //吸收回车
 
		//将消息存放到消息队列中
		msgsnd(msqid, &buf, SIZE, 0);
 
		printf("发送成功\n");
 
		if(strcmp(buf.mtext, "quit") == 0)
		{
			break;
		}
	}

	if(msgctl(msqid,IPC_RMID,NULL)==-1)
	{
		perror("delete error");
		return -1;
	}
 
	return 0;
}