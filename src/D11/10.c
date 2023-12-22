/*
 * Filename: 10.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int my_sum(int n){
	if(n==0)
		return 0;
	else{
		return n+my_sum(n-1);
	}

}

int my_factorial(int n){
	if(n==0)
		return 1;
	else{
		return n*my_factorial(n-1);
	}
}

int main(int argc,const char *argv[]){
	int n;
	scanf("%d",&n);
	printf("sum(%d)=%d\n",n,my_sum(n));
	printf("factorial(%d)=%d\n",n,my_factorial(n));

	return 0;
}


