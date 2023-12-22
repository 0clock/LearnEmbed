#include <stdio.h>

void YanhuiTri(int n){
	int arr[n][n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++){
			if(j==0||i==j){
				arr[i][j]=1;
			}else{
				arr[i][j]=arr[i-1][j]+arr[i-1][j-1];
			}

			printf("%-3d",arr[i][j]);

		}
		puts(" ");
	}
}

int main(int argc, const char *argv[]){
	int a;
	scanf("%d",&a);

	YanhuiTri(a);
	return 0;
}
