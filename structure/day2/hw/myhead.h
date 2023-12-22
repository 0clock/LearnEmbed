#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct goods{
	char name[10];
	unsigned int price;
	unsigned int count;
	unsigned int number;
	char descrip[20];
}goods_t;

goods_t *creat(unsigned int n);
void input(goods_t *p,unsigned int n);
void bubble(goods_t *p,unsigned int n);
goods_t* Max(goods_t *p,unsigned int n);
int Money(goods_t *p,unsigned int n);
void output(goods_t *p,unsigned int n);
int* free_space(int *p);


#endif
