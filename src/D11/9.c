/*
 * Filename: 9.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

void fun(int i){
	if(i==0)
		return;
	else{
		printf("i=%d\n",i);

		fun(i-1);
	}
}

int main(int argc,const char *argv[]){
	fun(5);
	return 0;
}


