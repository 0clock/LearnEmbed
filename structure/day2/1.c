/*
 * Filename: 1.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

typedef int arr_t[2][3];
int main(int argc,const char *argv[]){
	arr_t a={11,22,33,44,55,66};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%-4d",a[i][j]);
		}
		puts("");
	}
	return 0;
}


