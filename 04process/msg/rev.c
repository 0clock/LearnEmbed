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

// 定义消息结构体类型
struct msgbuf
{
	long mtype;		  // 消息类型
	char mtext[4096]; // 消息正文
};

// 定义一个宏，表示正文大小
#define SIZE (sizeof(struct msgbuf) - sizeof(long))



int main(int argc, const char *argv[])
{
	// 1、创建key值
	key_t key = 0;
	if ((key = ftok("/", 't')) == -1)
	{
		perror("fork error");
		return -1;
	}

	printf("key = %#x\n", key);

	// 2、使用key值创建一个消息队列
	int msqid = 0;
	if ((msqid = msgget(key, IPC_CREAT | 0664)) == -1)
	{
		perror("msgget error");
		return -1;
	}

	printf("msqid = %d\n", msqid);

	// 此时就已经在内核空间创建出消息队列了
	// 定义一个消息类型的容器
	struct msgbuf buf;

	// 3、循环向消息队列中存放数据
	while (1)
	{
		// 从消息队列中读取消息
		msgrcv(msqid, &buf, SIZE, 0, 0);
		// 第一个0表示无视类型，每次都取第一个消息
		// 第二个0表示阻塞形式接收消息

		printf("收到消息为：%s\n", buf.mtext);

		if (strcmp(buf.mtext, "quit") == 0)
		{
			break;
		}
	}

	return 0;
}