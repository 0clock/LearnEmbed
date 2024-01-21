#ifndef _MY_UDP_H_
#define _MY_UDP_H_

#include "header.h"
#include "linklist.h"



#define SER_PORT 8888
#define SER_IP "192.168.117.128"

enum msg_type_t{
    LOGIN,
    CHAT,
    QUIT,
    BOCST
};
struct msg_t
{
    enum msg_type_t type;
    char username[128];
    char msg[1024];
};


extern struct sockaddr_in server_sin, client_cin;
extern int sfd;
extern struct msg_t *user_msg;
extern socklen_t socklen ;

int udp_init();
int server_recv();
int server_send();

#endif