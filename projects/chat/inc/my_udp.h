#ifndef _MY_UDP_H_
#define _MY_UDP_H_

#include "header.h"
#include "linklist.h"



#define SER_PORT 8888
#define SER_IP "192.168.117.128"

enum msg_type_t{
    LOGIN,
    CHAT,
    QUIT
};
struct msg_t
{
    enum msg_type_t type;
    char msg[1024];
};


extern struct sockaddr_in server_sin;
extern int sfd;
extern struct msg_t *user_msg;


int udp_init();
int server_recv();

#endif