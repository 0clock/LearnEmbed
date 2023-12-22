/*
 * Filename: 2.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>
#include <string.h>
struct BOOK{
	char name[20];
	int isbn;
	char auther[20];
};

struct BOOK a={"aaa",112233,"linus"};

struct BOOK b={.auther="jun",.isbn=233333,.name="bbb"};


void output(struct BOOK book){
	printf("书名\t ISBN\t\t 作者\n");
	printf("%s\t%d\t\t%s\t",book.name,book.isbn,book.auther);
	puts("");
}

int main(int argc,const char *argv[]){
	output(a);
	output(b);
	struct BOOK c;
	strcpy(c.name,"ccc");
	char *arr[10];
	char brr[10]="Hello";
	arr=brr;
	puts(*arr);
	c.isbn=3333333;
	strcpy(c.auther,"June");
	output(c);

	return 0;
}


