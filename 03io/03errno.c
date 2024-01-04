/*
 * Filename: errno.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, const char *argv[]){
	//定义文件指针
	FILE *fp=NULL;

	//以只读的形式打开当前文件路劲下的test.txt文件
	fp=fopen("./test.txt","r");
	if(NULL==fp){
		perror("open file:");
		return -1;
	}
	perror("");

	fclose(fp);

	return 0;
}
