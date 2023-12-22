#include <stdio.h>

int main(int argc, const char *argv[]){
	char a[20];
	gets(a);

	size_t len=0;

	for (int i = 0; a[i]!=0 ; i++){
		len++;
	}
	
	for (int i = 0; i < len-1 ; i++){
		for (int j = 0; j < len-1 ; j++){
			if(a[j]>a[j+1]){
				char temp = a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	
	puts(a);

	return 0;
}
