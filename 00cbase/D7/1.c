#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
	char str[]="hellok";
	int i=0,j=strlen(str)-1;
	while(i<j){
		char t=str[i];
		str[i]=str[j];
		str[j]=t;
		i++;j--;
	}
	printf("%s\n",str);
}
