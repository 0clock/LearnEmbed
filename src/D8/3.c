#include <stdio.h>

int main(int argc, const char *argv[]){
	

	int arr[2][3];

	int line=sizeof(arr)/sizeof(arr[0]);
	int cow=sizeof(arr[0])/sizeof(arr[0][0]);

	int rra[cow][line];
	
	for (int i = 0 ; i < line ; i++){
		for (int j = 0; j < cow; j++){
			scanf("%d",&arr[i][j]);
			rra[j][i]=arr[i][j];
		}
	}

	for (int i = 0 ; i < cow ; i++){
		for (int j = 0; j < line; j++){
			printf("%-4d",rra[i][j]);
		}
		puts(" ");
	}
	return 0;
}
