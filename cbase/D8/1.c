#include <stdio.h>

int main(int argc, const char *argv[]){
	float arr[3][5];
	
	for (int i = 0; i < 3*5; i++){
		scanf("%f",&arr[0][i]);
	}

	float sum=0;

	for (int i = 0; i < 3*5; i++){
		sum+=arr[0][i];
		printf("%f ",arr[0][i]);
	}

	printf("\nsum=%f\n",sum);

	return 0;
}
