/*
 * Filename: 5.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Car{
	char name[10];
	int price;
};

struct Car *start(struct Car *p){
	p=(struct Car *)malloc(sizeof(sizeof(struct Car)*2));
	if(NULL==p)
		return NULL;
	return p;
}

void input(struct Car *p){
	for (int i = 0; i < 2; i++) {
		printf("Please Enter %d Name:",i+1);
		scanf("%s",(p+i)->name);
		printf("Please Enter %d Price:",i+1);
		scanf("%d",&(p+i)->price);
	}
}

void output(struct Car *p){
	printf("品牌\t价格\n");
	for (int i = 0; i < 2; i++) {
		printf("%s\t%d\n",(p+i)->name,(p+i)->price);
	}
}

struct Car *my_free(struct Car *p){
	free(p);
	return NULL;
}

int main(int argc,const char *argv[]){
	struct Car *p;

	p=start(p);
	input(p);
	output(p);
	p=my_free(p);

	return 0;
}


