/*
 * Filename: 1.c
 * Author: linus
 * Date: 2023-12-18
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>
#include <unistd.h>
int main(int argc,const char *argv[]){
	for(int i=0;i<100000;i++){
		printf("i=%d\n",i);
		sleep(1);
	}	
	return 0;
}


