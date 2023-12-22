#include <stdio.h>

int main(int argc, const char *argv[]){
	int a=100;
	int *p=&a;
	printf("地址：%p %p %p %p\n",p,&a,&*p,&(*p));
	printf("值：%d %d %d %d\n",a,*p,*&a,*(&a));
	return 0;
}
