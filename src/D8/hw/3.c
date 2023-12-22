#include <stdio.h>

int main(int argc, const char *argv[]){
	int line1=0,cow1=0;
	printf("line1 cow1:");
	scanf("%d %d",&line1,&cow1);
	int line2=0,cow2=0;
	printf("line2 cow2:");
	scanf("%d %d",&line2,&cow2);

	if(cow1!=line2){
		printf("error!\n");
		return 0;
	}

	int a[line1][cow1],b[line2][cow2],ans[20][20]={0};

	printf("a:\n");
	for (int i = 0; i < line1 ; i++){
		for (int j = 0; j < cow1; j++){
			scanf("%d",&a[i][j]);
		}
	}
	
	printf("b:\n");
	for (int i = 0; i < line2 ; i++){
		for (int j = 0; j < cow2; j++){
			scanf("%d",&b[i][j]);				
		}
	}

	
	for (int i = 0; i < line1 ; i++){
		for (int j = 0; j < cow2; j++){
			for (int k = 0; k < line2; k++){
				ans[i][j]+=a[i][k]*b[k][j];
			}

			printf("%-4d",ans[i][j]);
		}
		puts(" ");
	}







	return 0;
}
