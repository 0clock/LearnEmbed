/*
 * Filename: main.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include "myhead.h"
int main(int argc,const char *argv[]){
	goods_t *p;
	p=creat(5);	
	input(p,5);
	bubble(p,5);
	output(p,5);
	return 0;
}


