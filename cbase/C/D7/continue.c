#include <stdio.h>

void main(){
	for(int i=0;i<=100;i++){
		if(i%7==0||i%10==7||i/10==7){
			continue;
		}
		printf("i=%d	",i);
	}
	printf("\n");
}
