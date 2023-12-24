#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void Rev(int line,int row,int a[line][row]);
int main(int argc, const char *argv[]){
	int a[][4]={1,2,3,4,5,6,7,8,9,10,11,12};
	int line=sizeof(a)/sizeof(a[0]);
	int row=sizeof(a[0])/sizeof(a[0][0]);
	Rev(line,row,a);
	return 0;
}

void Rev(int line,int row,int a[line][row]){
	int b[row][line];
	for(int i=0;i<line;i++){
		for(int j=0;j<row;j++){
			b[j][i]=a[i][j];
		}
	}

	for(int i=0;i<row;i++){
		for(int j=0;j<line;j++){
			printf("%-3d",b[i][j]);
		}
		puts("");
	}
}

