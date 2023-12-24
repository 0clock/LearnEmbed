#include <stdio.h>
#include <string.h>
int main(int argc, const char *argv[]){
	char a[20],b[20];
	gets(a);
	gets(b);

	int i=0;
	while(a[i]!='\0'){
		i++;
	}
	
	int j=0;
	while(b[j]!='\0'){
		a[i++]=b[j++];
	}

	a[i]='\0';

	puts(a);


	return 0;
}
