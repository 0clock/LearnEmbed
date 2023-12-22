#include <stdio.h>

int main(int argc, const char *argv[]){
	char arr[20];
	gets(arr);

	size_t count=0;

	for (int i = 0; arr[i]!='\0' ; i++){
		if(arr[i]==' '){
			count++;
		}
	}
	
	printf("空格的个数是：%ld\n",count);

	return 0;
}
