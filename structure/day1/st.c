/*
 * Filename: st.c
 * Author: linus
 * Date: 2023-12-19
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include "myhead.h"

int* creat(){
	int *p=(int*)malloc(sizeof(int)*5);
	if(NULL==p)
		return NULL;
	return p;
}

void input(int *p){
	for (int i = 0; i < 5; i++) {
		printf("Please enter %d element:",i+1);
		scanf("%d",p+i);
	}
}

void output(int *p){
	for (int i = 0; i < 5; i++) {
		printf("%-4d",*(p+i));
	}
	puts("");

}

int* free_space(int *p){
	if (NULL==p){
		return NULL;
	}

	free(p);
	p=NULL;
	return p;
}

