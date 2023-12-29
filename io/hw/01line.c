/*
 * Filename: 01line.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include <stdio.h>

int main(int argc, const char *argv[]){
	FILE *fp=NULL;
	if(argc!=2){
		puts("输入有误");
		puts("eg:/a.out test.txt");
		return -1;
	}
	if((fp=fopen(argv[1],"r"))==NULL){
		perror("fopen error:");
		return -1;
	}

	int line=0;
	//char buff=0;

	char buff[128];
	while(NULL!=fgets(buff,sizeof(buff),fp)){
		line++;
	}

	printf("此文件有%d行\n",line);
	fclose(fp);
	return 0;
}
