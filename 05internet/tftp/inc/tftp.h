#ifndef _TFTP_H_
#define _TFTP_H_

#include "header.h"

#define SER_PORT 69
#define SER_IP "192.168.117.1"

#define CMD_RRQ (short)1
#define CMD_WRQ (short)2
#define CMD_DATA (short)3
#define CMD_ACK (short)4
#define CMD_ERROR (short)5
#define CMD_LIST (short)6
#define CMD_HEAD (short)7



int tftp_download ();

#endif