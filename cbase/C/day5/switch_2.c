#include <stdio.h>

void main(){
	int date;
	printf("input(eg.20231201):");
	scanf("%d",&date);
	int year=date / 10000;
	int mon=(date%10000)/100;
	int day=(date%100);
	printf("%d %d %d",year,mon,day);

}
