#include <stdio.h>

void main(){
	int l = 0;
	scanf("%d",&l);
	for(int i = 1;i <= l;i++){
		for(int j=1;j<i;j++){
			printf(" ");
		}

		for(int k=1;k<=2*l-2*i+1;k++){
			printf("#");
		}

		printf("\n");
	}	
}
