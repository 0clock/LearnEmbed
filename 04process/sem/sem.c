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

union semun
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                              (Linux-specific) */
};

// 定义设置信号灯集中的灯的值函数
int set_semno_value(int semid, int semno)
{
    int val;
    printf("请输入第%d号灯的值：", semno);
    scanf("%d", &val);

    // 定义一个共用体变量
    union semun su;
    su.val = val;
    // 调用控制函数
    if (semctl(semid, semno, SETVAL, su) == -1)
    {
        perror("semctl error");
        return -1;
    }
    return 0;
}

// 创建sem
int sem_creat(int semcount)
{
    // 1.获取key值
    key_t key = 0;
    if ((key = ftok("/", 'K') == -1))
    {
        perror("ftok error");
        return -1;
    }

    // 2.通过key值创建信号灯集
    int semid = 0;
    if ((semid = semget(key, semcount, IPC_CREAT | IPC_EXCL | 0664)) == -1)
    {
        if (errno == EEXIST)
        {
            return semget(key, semcount, IPC_CREAT | 0664);
        }
        perror("semget error");
        return -1;
    }

    // 3.初始化信号灯集中的灯
    for (int i = 0; i < semcount; i++)
    {
        // 给semid信号灯集中的i号灯设置值
        set_semno_value(semid, i);
    }
    // 4.返回信号灯集
}

// 获取sem资源
int sem_wait(int semid, int semno)
{
    // 定义操作结构体
    struct sembuf buf;
    buf.sem_num = semno; // 要操作的信号灯的编号
    buf.sem_op = -1;     // 表示申请资源操作
    buf.sem_flg = 0;     // 阻塞申请资源

    // 执行申请资源操作
    if (semop(semid, &buf, 1) == -1)
    {
        perror("semop error");
        return -1;
    }

    return 0;
}

// 释放sem资源
int sem_post(int semid, int semno)
{
    // 定义操作结构体
    struct sembuf buf;
    buf.sem_num = semno; // 要操作的信号灯的编号
    buf.sem_op = 1;      // 表示申请资源操作
    buf.sem_flg = 0;     // 阻塞申请资源

    // 执行申请资源操作
    if (semop(semid, &buf, 1) == -1)
    {
        perror("semop error");
        return -1;
    }

    return 0;
}

int delete_sem(int semid)
{
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl error");
        return -1;
    }

    return 0;
}