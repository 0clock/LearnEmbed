/*
 * Filename: 7.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int my_sum(int a,int b){
	return a+b;
}

int my_sub(int a,int b){
	return a-b;
}

int my_mul(int a,int b){
	return a*b;
}

int my_div(int a,int b){
	return a/b;
}



int main(int argc,const char *argv[]){
	int a=6,b=5;
	int (*p[4])(int,int)={my_sum,my_sub,my_mul,my_div};

	printf("%ld %ld\n",sizeof(p),sizeof(int(*[8])(int,int)));

	for (int i = 0; i < 4; i++) {
		printf("%d\n",p[i](a,b));
		printf("%d\n",(*(p+i))(a,b));
	}

	return 0;
}


