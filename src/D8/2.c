#include <stdio.h>

int main(int argc, const char *argv[]){
	int n;

	scanf("%d",&n);

	int arr[n][n];

	for (int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++){
			if( j==0 || j==i ){
				arr[i][j]=1;
			}else{
				arr[i][j]=arr[i-1][j]+arr[i-1][j-1];
			}
			printf("%-4d ",arr[i][j]);
		}
		puts(" ");
	}
	
	return 0;
}
