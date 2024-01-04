#include <stdio.h>
int SecMax(int line,int row,int (*p)[row]);
int main(int argc, const char *argv[]){
	int line,row;
	printf("enter line&row:");
	scanf("%d %d",&line,&row);
	int arr[line][row];

	for (int i = 0; i < line; i++){
		for (int j = 0; j < row; j++){
			scanf("%d",*(arr+i)+j);
		}
	}

	int second =SecMax(line,row,arr);
	printf("Second=%d\n",second);

	return 0;
}

int SecMax(int line,int row,int (*p)[row]){
	int max=**p;
	int min=**p;
	int maxi=0,maxj=0;

	for (int i = 0; i < line; i++){
		for (int j = 0; j < row; j++){
			if(max<*(*(p+i)+j)){
				max=*(*(p+i)+j);
				maxi=i;
				maxj=j;
			}
			if(min>*(*(p+i)+j))
				min=*(*(p+i)+j);
		}
	}

	int second=min;
	for(int i=0;i<line;i++){
		for (int j = 0; j < row; j++){
			if(maxi==i && maxj==j)
				continue;
			if(second<*(*(p+i)+j))
				second=*(*p+i)+j;
		}
	}

	return second;
}
