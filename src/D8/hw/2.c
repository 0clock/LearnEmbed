#include <stdio.h>

int main(int argc, const char *argv[]){
	char arr[20];
	gets(arr);

	size_t count=0;

	int i =0;
	
	while(arr[i]!='\0'){

		if(arr[i]!=' ' && (arr[i+1]==' '||arr[i+1]=='\0')){
			count++;
		}

		i++;
	}
	
	printf("单词的个数是：%ld\n",count);

	return 0;
}
