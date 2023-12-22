#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef int datatype;

//创建节点结构体
typedef struct Node {
	datatype data;
	struct Node* next;
}*linklist;

enum STATE {
	error=-1,
	success
};

linklist creat_node();
linklist insert_head(linklist head,datatype element);
void output(linklist list);
linklist insert_rear(linklist list,datatype element);
linklist delete_head(linklist list);
linklist delete_rear(linklist list);
linklist insert_pos(linklist list,int pos,datatype element);
linklist delete_pos(linklist list,int pos);
datatype find_pos(linklist list,int pos);
void update_pos(linklist list,int pos,datatype element);
linklist invert(linklist list);
#endif
