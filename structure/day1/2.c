/*
 * Filename: 2.c
 * Author: linus
 * Date: 2023-12-19
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

#define MAX(a,b,c) ({int max=a;\
		if(max<=b)\
			max=b;\
		if(max<=c)\
			max=c;\
		max;})

#define MAX1(a,b,c) a>b?(a>c?a:c):(b>c?b:c)

#define MAX2(a,b,c) do{int max=a;\
	if(max<=b)\
		max=b;\
	if(max<=c)\
		max=c;\
	printf("max=%d\n",max);\
	}while(0)

int main(int argc,const char *argv[]){
	printf("Max=%d\n",MAX(100,200,300));
	printf("Max1=%d\n",MAX1(100,200,300));
	MAX2(100,200,50);
	return 0;
}


