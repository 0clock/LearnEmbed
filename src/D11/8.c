/*
 * Filename: 8.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int main(int argc,const char *argv[]){
	int a=111;
	void *p=&a;
	printf("*p=%d\n",*(int*)p);
	return 0;
}


