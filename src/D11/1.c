/*
 * Filename: 1.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int main(int argc,const char *argv[]){
	int a=1,b=2,c=3,d=4;
	int *p[]={&a,&b,&c,&d};
	printf("sizeof(p)=%ld\n",sizeof(p));
	printf("%ld\n",sizeof(int *[4]));
	int n=sizeof(p)/sizeof(p[0]);
	for (int i = 0; i < n; i++) {
		printf("**(p+i)=%d \n",**(p+i));
		printf("*p[i]=%d \n",*p[i]);
		printf("p[i]=%p \n",p[i]);
		printf("p+i=%p \n",p+i);
	}
	return 0;
}


