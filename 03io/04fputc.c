/*
 * Filename: 04fputc.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 

#include <stdio.h>
#include <string.h>
int main(int argc, const char *argv[]){

	//定义文件指针
	FILE *fp=0;

	//以只写的形式打开文件
	if((fp=fopen("./test.txt","w"))==NULL){
		perror("fopen:");
		return -1;
	}

	//向文件中写入字符
	fputc('H',fp);
	fputc('E',fp);
	fputc('L',fp);
	fputc('L',fp);
	fputc('O',fp);
	fputc('\n',fp);
	
	//关闭文件
	fclose(fp);

	//重新以只读的形式打开文件
	if((fp=fopen("./test.txt","r"))==NULL){
		perror("fopen r reeor");
		return -1;
	}

	char buf = 0;
	while((buf=fgetc(fp))!=EOF){
		printf("%c",buf);
	}
	fclose(fp);

	return 0;
}
