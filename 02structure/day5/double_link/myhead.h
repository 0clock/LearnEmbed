#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef char datatype;

//创建节点结构体
typedef struct Node {
	datatype data;
	struct Node* next;
	struct Node* priv;
}*doublelink;


enum STATE {
	error=-1,
	success
};
doublelink creat_node();
doublelink insert_head(doublelink head,datatype element);
#endif
