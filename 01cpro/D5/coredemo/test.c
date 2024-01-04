#include <stdio.h>

char *fun(){
	char str[]="hello";
	return str;
}

int main(int argc,const char *argv[]){
	char *p=NULL;
	p=fun();
	printf("%c",*p);
	return 0;
}


