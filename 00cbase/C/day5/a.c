#include <stdio.h>

void main(){
	int n;
	scanf("%d",&n);
	if(n%3==0){
		printf("%d是三的倍数\n",n);
		if(n%7==0){
			printf("是七的倍数\n");
		}
	}

	scanf("第二题：");
}
