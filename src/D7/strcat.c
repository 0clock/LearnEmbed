#include <stdio.h>
#include <stdlib.h>
void main(){
	char dest[20]="good\0";
	char src[]="study";
	long int count=0;
	for(int i=0;dest[i]!='\0';i++){
		count++;
	}

	for(int i=0;src[i]!='\0';i++){
		dest[count]=src[i];
		count++;
	}
	dest[count]='\0';
	puts(dest);

}
