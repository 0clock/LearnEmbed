#include "header.h"
#include "linklist.h"
#include "loger.h"
#include "p_thread.h"
#include "my_udp.h"

#define SERVER

// 使用多线程

int main(int argc, const char *argv[])
{
    user_msg=(struct msg_t*)malloc(sizeof(struct msg_t));
    udp_init();

    thread_init();
    while (1);
    
}
