/*
 * Filename: commodity.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include "myhead.h"
goods_t* creat(unsigned int n){
	goods_t *p;
	p=(goods_t *)malloc(sizeof(goods_t)*n);
	return p;
}

void input(goods_t *p,unsigned int n){
	puts("begin input!");
	for (int i = 0; i < n; i++) {
		puts("############################");
		printf("Please Enter goods %d:\n",i+1);
		printf("name:");
		scanf("%s",(p+i)->name);
		printf("price:");
		scanf("%d",&(p+i)->price);
		printf("count:");
		scanf("%d",&(p+i)->count);
		printf("Description:");
		scanf("%s",(p+i)->descrip);
	}
	puts("finish input!");
}
void bubble(goods_t *p,unsigned int n){
	puts("begin bubble...");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if((p+j)->price>(p+j+1)->price){
				goods_t tmp=*(p+j);
				*(p+j)=*(p+j+1);
				*(p+j+1)=tmp;
			}
		}
	}
	puts("finish bubble.");
}

goods_t *Max(goods_t *p,unsigned int n){
	//puts("Max...");
	goods_t *Max=p;
	for (int i = 0; i < n; i++) {
		if((Max->price) < ((p+i)->price)){
			Max=(p+i);
		}
	}
	//puts("finish Max.");
	return Max;
}


int Money(goods_t *p,unsigned int n){
	//puts("Money...");
	int sum=0;
	for (int i = 0; i < n; i++) {
		sum+=((p+i)->price)*((p+i)->count);
	}
	//puts("finish Money.");
	return sum;
}

void output(goods_t *p,unsigned int n){
	puts("排序后的商品：");
	printf("名称\t\t单价\t\t数量\t\t描述\n");
	for (int i = 0; i < n; i++) {
		printf("%s\t\t",(p+i)->name);
		printf("%d\t\t",(p+i)->price);
		printf("%d\t\t",(p+i)->count);
		printf("%s\t\n",(p+i)->descrip);
	}
	
	puts("最贵的：");
	goods_t *mmm=Max(p,n);
	printf("name=%s\n",mmm->name);
	printf("price=%d\n",mmm->price);
	printf("Description=%s\n",mmm->descrip);

	puts("");

	puts("总价:");
	printf("%d\n",Money(p,n));

}
