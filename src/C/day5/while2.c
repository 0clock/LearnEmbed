#include <stdio.h>

void main(){
	int i=1,j=1;
	while(i<=9){
		while(j<=9){
			printf("%dx%d=%d  ",j,i,i*j);
			j++;
		}
		j=i+1;
		printf("\n");
		i++;
	}
}
