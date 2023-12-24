#include <stdio.h>

int main(int argc, const char *argv[]){
	char a[20],b[20],temp[20];
	
	gets(a);
	
	size_t len=0;
	for (int i = 0; a[i]!='\0' ; i++) {
		temp[i]=a[i];
		len++;
	}
	temp[len]='\0';
	puts(temp);
	for (int i = 0; temp[i]!='\0' ; i++) {
		a[i]=temp[len-i-1];
	}

	puts(a);

	return 0;
}
