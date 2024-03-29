#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <header.h>


typedef struct user_t
{
    char username[128];
    struct sockaddr_in cin;
} user;

typedef user datatype;

// 创建节点结构体
typedef struct Node
{
    datatype data;
    struct Node *next;
} *linklist;

enum STATE
{
    error = -1,
    success
};

linklist creat_node();
linklist insert_head(linklist head, datatype element);
void output(linklist list);
linklist insert_rear(linklist list, datatype element);
linklist delete_head(linklist list);
linklist delete_rear(linklist list);
linklist insert_pos(linklist list, int pos, datatype element);
linklist delete_pos(linklist list, int pos);
datatype find_pos(linklist list, int pos);
void update_pos(linklist list, int pos, datatype element);
linklist invert(linklist list);
linklist free_space(linklist head);
linklist joseph(linklist head, int n, int m);

#endif