/*
 * Filename: 05fgetc.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]){

	FILE *fp=NULL;
	FILE *fp_cp=NULL;
	if((fp=fopen("./test.txt","r"))==NULL){
		perror("fopen r:");
		return -1;
	}
	if((fp_cp=fopen("./cp_test.txt","w"))==NULL){
		perror("fopen w:");
		return -1;
	}

	char buff=0;
	int line=0;
	while((buff=fgetc(fp))!=EOF){
		fputc(buff,fp_cp);
		if(buff=='\n')
			line++;
	}
	printf("文件有%d行。\n",line);


	return 0;
}
