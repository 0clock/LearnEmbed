/*
 * Filename: 02cp.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int main(int argc, const char *argv[]){
	if(argc!=3){
		puts("输入有误！");
		return -1;
	}
	FILE* fp=NULL;
	FILE*fp_cp=NULL;
	if((fp=fopen(argv[1],"r"))==NULL){
		perror("打开1文件出错：");
		return -1;
	}

	if((fp_cp=fopen(argv[2],"w"))==NULL){
		perror("打开2文件出错：");
		return -1;
	}

	char buff[1024];
	while(fgets(buff,sizeof(buff),fp)!=NULL){
		fputs(buff,fp_cp);
	}

	puts("拷贝成功！");
	fclose(fp);
	fclose(fp_cp);
	return 0;
}
