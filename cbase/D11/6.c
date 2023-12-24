/*
 * Filename: 6.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

void fun(){
	printf("Hello World!\n");
}

int main(int argc,const char *argv[]){
	fun();
	(*fun)();

	void (*p)(void)=fun;

	printf("fun=%p\n",fun);
	printf("*fun=%p\n",*fun);

	printf("sizeof(fun)=%ld\n",sizeof(fun));
	printf("p=%p\n",p);
	printf("*p=%p\n",*p);

	printf("sizeof(p)=%ld\n",sizeof(p));

	p();
	(*p)();

	return 0;
}


