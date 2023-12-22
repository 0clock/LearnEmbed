#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main(){
	char str[]="hello world!";
	int len=strlen(str);
	//非函数实现：
	unsigned long count=0;
	for(int i=0;str[i]!='\0';i++){
		count++;
	}

	printf("%ld\n",count);

}
