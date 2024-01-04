/*
 * Filename: 5.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: 指针函数
 * 				目的：需要返回多个变量的值
 * 				在写时注意不可以返回局部变量的地址，生命周期太短
 */
 
#include <stdio.h>

int* fun(){
	int a=100,b=200;
	int arr[2];arr[0]=a,arr[1]=b;
	return arr;
}



int main(int argc,const char *argv[]){
	int* p=fun();	

	printf("*p=%d *(p+1)=%d\n",*p,*(p+1));

	return 0;
}


