/*
 * Filename: main.c
 * Author: linus
 * Date: 2023-12-18
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

char *fun(){
	char arr[]="hello";
	return arr;
}

int main(int argc,const char *argv[]){
	char *p=NULL;
	p=fun();

	printf("%c",*p);
	return 0;
}


