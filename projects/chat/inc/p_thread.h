#ifndef _P_THREAD_H_
#define _P_THREAD_H_
#include "header.h"

extern pthread_t tid1, tid2;

int thread_init();
int client_thread_init();
#endif