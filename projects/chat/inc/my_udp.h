#ifndef _MY_UDP_H_
#define _MY_UDP_H_

#include "header.h"

#define SER_PORT 9999
#define SER_IP "192.168.125.78"

extern struct sockaddr_in server_sin;

int udp_init();

#endif