#include <stdio.h>

void main(){
	int i=100,sum=0;
	do{
		sum=sum+i;
	}while(i--);

	printf("sum=%d\n",sum);
	
}
