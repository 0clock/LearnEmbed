/*
 * Filename: 08buffed.c
 * Author: linus
 * Date: 2024-01-02
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int main(int argc, const char *argv[]){
	// printf("Hello World\n");
	// while(1);

	// printf("Hello World");
	// fclose(stdout);
	// while (1);


	// printf("Hello World!");
	// fflush(stdout);
	// while(1);
	// int num = 0;
	// printf("请输入num");
	printf("%ld\n", stdout->_IO_buf_end - stdout->_IO_buf_base);    //未使用时，大小为0
	printf("%ld\n", stdout->_IO_buf_end - stdout->_IO_buf_base);    //行缓存1024

	return 0;
}
