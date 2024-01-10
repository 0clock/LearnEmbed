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

int userid = 0;

char username1[128];
char username2[128];

// 定义消息结构体类型
struct message
{
    long mtype;       // 消息类型
    char mtext[4096]; // 消息正文
};

// 1、创建key值
key_t key = 0;
// 2、使用key值创建一个消息队列
int msgid = 0;

// 定义一个宏，表示正文大小
#define SIZE (sizeof(struct msgbuf) - sizeof(long))

// 此时就已经在内核空间创建出消息队列了

// 发送消息的函数
void send_message(int msgid, long mtype, const char *sender, const char *receiver)
{
    struct message msg;
    msg.mtype = mtype;
    printf("[%s] Enter a message for %s: ", sender, receiver);
    fgets(msg.mtext, sizeof(msg.mtext), stdin);

    // 发送消息
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

// 接收消息的函数
void receive_message(int msgid, long mtype, const char *receiver)
{
    struct message msg;

    // 接收消息
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), mtype, 0) == -1)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    // 打印接收到的消息
    printf("[%s] Received message: %s\n", receiver, msg.mtext);
}

void *receive(void *arg)
{
    // 3、循环向消息队列中存放数据
    while (1)
    {
        receive_message(msgid, 1, username1);
    }
}

void *send(void *arg)
{
    while (1)
    {
        send_message(msgid, 2, username1, username2);
    }
}

int main(int argc, const char *argv[])
{
    if ((key = ftok("/", 'a')) == -1)
    {
        perror("fork error");
        return -1;
    }

    if ((msgid = msgget(key, IPC_CREAT | 0664)) == -1)
    {
        perror("msgget error");
        return -1;
    }

    printf("请输入您的用户名：");
    fgets(username1, sizeof(username1), stdin);

    // printf("等待其他用户上线。\n");
    printf("请输入对方的用户名：");
    fgets(username2, sizeof(username2), stdin);
    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, receive, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }

    if (pthread_create(&tid2, NULL, send, NULL) != 0)
    {
        printf("tid1 creat error\n");
        return -1;
    }

    printf("线程创建成功！\n");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}