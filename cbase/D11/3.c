/*
 * Filename: 3.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: 终端输入实现计算器
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,const char *argv[]){
	int num1=atoi(argv[1]);
	int num2=atoi(argv[3]);

	switch (*argv[2]){
		case '+':
			printf("%d\n",num1+num2);
			break;
		case '-':
			printf("%d\n",num1-num2);
			break;
		case '*':
			printf("%d\n",num1*num2);
			break;
		case '/':
			printf("%f\n",(float)num1/num2);
			break;
		case '%':
			printf("%d\n",num1%num2);
			break;
		default:
			break;
	}
	return 0;
}


