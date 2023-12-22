#include <stdio.h>
//水仙花数
void main(){
	int n=100;
	while(n<1000){
		if((n/100)*(n/100)*(n/100)+(n%100/10)*(n%100/10)*(n%100/10)+(n%10)*(n%10)*(n%10)==n){
			printf("%d是水仙花数\n",n);
		}
		n++;
	}
}
