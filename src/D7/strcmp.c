#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main(){
	char str1[10];
	char str2[10];
	gets(str1);
	gets(str2);
	int temp=strcmp(str1,str2);
	/*
	if(temp>0){
		puts("str1>srt2");
	}else if(temp==0){
		puts("str1=str2");
	}else{
		puts("str1<str2");
	}
	*/


	int i=0;	
	while(str1[i]==str2[i]){
		if(str1[i]=='\0'){
			break;
		}
		i++;
	}

	int sub=str1[i]-str2[i];

	
	if(sub>0){
		puts(">");
	}else if(sub==0){
		puts("=");

	}else{
		puts("<");
	}
	
}
