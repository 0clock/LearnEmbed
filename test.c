/*
 * Filename: test.c
 * Author: linus
 * Date: 2024-01-13
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

char* sort(char *src)
{
	int i = 0;
	int len=strlen(src);
	int j=len-2;
	while(i<j)
	{
		char t=*(src+i);
		*(src+i)=*(src+j);
		*(src+j)=t;
		i++;
		j--;
	}
	*(src+len-1)='\0';
	return src;
}

int strcmp(const char* a,const char* b){
	int i=0;
	if(strlen(a)!=strlen(b)){
		return 0;
	}
	while(*(a+i)!='\0'||*(b+i)!='\0'){
		if(*(a+i)!=*(b+i)){
			return 0;
		}else{
			i++;
		}
	}
	
	return 1;

}

int main(int argc, const char *argv[])
{
	if(strcmp("hello","bbbbbb")==1){
		printf("相等\n");
	}else{
		printf("不相等\n");
	}
	return 0;
}
