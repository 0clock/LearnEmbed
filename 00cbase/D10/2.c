#include <stdio.h>

void YanghunTri_P(int line,int (*p)[line]);
int main(int argc, const char *argv[]){
	int arr[50][50];

	int line;
	scanf("%d",&line);
	
	YanghunTri_P(line,arr);	
	return 0;
}

void YanghunTri_P(int line,int (*p)[50]){
	for (int i =0 ; i < line; i++){
		for (int k = 0; k < line-i; k++){
			printf("%-2s"," ");
		}
		for (int j = 0; j <= i; j++){
			if(j==0||j==i){
				*(*(p+i)+j)=1;
			}else{
				*(*(p+i)+j)=*(*(p+i-1)+j-1)+*(*(p+i-1)+j);
			}
			printf("%-4d",*(*(p+i)+j));
		}

		puts(" ");
	}
}
