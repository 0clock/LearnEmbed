#include <stdio.h>

int main(int argc, const char *argv[]){
	int arr[]={11,22,33,44};
	int *p=arr;

	printf("&arr[0]=%p\n",&arr[0]);
	printf("&arr[0]+1=%p\n",&arr[0]+1);
	
	printf("arr=%p\n",arr);
	printf("arr+1=%p\n",arr+1);
	
	printf("&arr=%p\n",&arr);
	printf("&arr+1=%p\n",&arr+1);
	
	printf("&p[0]=%p\n",&p[0]);
	printf("&p[0]+1=%p\n",&p[0]+1);

	printf("p=%p\n",p);
	printf("p+1=%p\n",p+1);

	printf("&p=%p\n",&p);
	printf("&p+1=%p\n",&p+1);
	return 0;
}
