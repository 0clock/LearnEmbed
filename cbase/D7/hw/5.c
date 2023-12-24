#include <stdio.h>
#include <string.h>
int main(int argc, const char *argv[]){
	char a[20],b[20],temp[20];
	gets(a);
	gets(b);

	int i=0;
	for (i = 0 ; a[i]!='\0' ; i++){
		a[i]=b[i];
	}
	a[i]='\n';
	puts(a);
	puts(b);

	return 0;
}
