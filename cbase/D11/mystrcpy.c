/*
 * Filename: 6.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: my_strcpy
 */
 
#include <stdio.h>


char *my_strcpy(char *dest,char *src);
int main(int argc,const char *argv[]){
	char dest[20]="abc",src[20]="hello";

	char *(*q)(char *,char*)=my_strcpy;

	char *p=q(dest,src);
	puts(p);
	return 0;
}

char *my_strcpy(char *dest,char *src){
	int i;
	for (i = 0; *(src+i)!='\0' ; i++) {
		*(dest+i)=*(src+i);
	}
		
	*(dest+i)='\0';

	return dest;
}
