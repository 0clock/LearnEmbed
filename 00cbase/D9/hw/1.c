/*
 * Filename: 1.c
 * Author: linus
 * Date: 2023-12-10
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>
#include <string.h>
int main(int argc,const char *argv[]){
	printf("strlen=%ld\n",strlen("A\0B\0c"));	
	return 0;
}


