#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 10

enum A{
	FALSE=-1,
	SUCCESS
};


typedef int datatype;

typedef struct list{
	datatype data[MAXSIZE];
	int len;
}sqlist;

int isEmpty(sqlist* list);
int output(sqlist *list);
int insert_rear(sqlist* list,datatype element);
int isFull(sqlist* list);
sqlist* creat_list();
int delete_rear(sqlist* list);
void search_index(sqlist* list,int index);    
void update_index(sqlist* list,int index,datatype element); 
int delete_index(sqlist* list,int index);
int insert_index(sqlist* list,int index,datatype element);
int search_key(sqlist* list,datatype key);
int delete_key(sqlist* list,datatype key);
int change_key(sqlist* list,datatype key,datatype new);
int deduplicate(sqlist* list);
int sort(sqlist* list);
sqlist* my_free(sqlist* list);
#endif
