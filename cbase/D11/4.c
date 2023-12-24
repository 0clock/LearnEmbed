/*
 * Filename: 4.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int main(int argc,const char *argv[]){
	int a=100;
	int *p=&a;
	int **q=&p;
	int ***m=&q;

	printf("sz(p)=%ld  %ld\n",sizeof(p),sizeof(int *));
	printf("sz(q)=%ld  %ld\n",sizeof(q),sizeof(int **));
	printf("sz(m)=%ld  %ld\n",sizeof(m),sizeof(int ***));
	
	printf("a=%d *p=%d **q=%d ***m=%d\n",a,*p,**q,***m);
	printf("&a=%p p=%p *q=%p **m=%p\n",&a,p,*q,**m);
	printf("&p=%p q=%p *m=%p\n",&p,q,*m);
	printf("&q=%p m=%p\n",&q,m);

	return 0;
}


