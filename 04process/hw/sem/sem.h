#ifndef _SEM_H_
#define _SEM_H_

// 创建sem
int sem_creat(int semcount);

// 获取sem资源
int sem_wait(int semid,int semno);

// 释放sem资源
int sem_post(int semid,int semno);

int delete_sem(int semid);

#endif