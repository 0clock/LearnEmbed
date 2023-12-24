/*
 * Filename: 2.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: 字符指针数组
 */
 
#include <stdio.h>

int main(int argc,const char *argv[]){
	char str1[]="abcde",str2[]="ASDFGHGJKL",str3[]="12345678";
	char *p[]={str1,str2,str3};

	for (int i = 0; i < 3; i++) {
		puts(p[i]);
		puts(*(p+i));
	}
	//修改
	*(p[1]+1)='s';
	*(*(p+1)+2)='d';
	puts(p[1]);


	char *q[]={"abcde","ASDFGHJK","13245678"};
	//不可修改
	*(q[1]+1)='s';
	*(*(q+1)+2)='d';
	puts(q[1]);
	puts(q[1]);


	return 0;
}


