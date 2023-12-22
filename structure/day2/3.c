/*
 * Filename: 3.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>
#include <string.h>
struct Car{
	char name[10];
	int price;
	char color[10];
};

void outputs(struct Car a[], int n){
	printf("品牌\t价格\t颜色\t\n");
	for (int i = 0; i < n; i++) {
		printf("%s\t%d\t%s\n",a[i].name,a[i].price,a[i].color);
	}

	puts("");
}

int main(int argc,const char *argv[]){
	struct Car a[]={{"Giant",2500,"灰"},{"小刀",1280,"绿"}};

	outputs(a,2);

	struct Car b[]={
		[1]={.name="光轮2000",.price=999999,.color="木色"},
		[0]={.name="永恒号",.price=999999999,.color="Ti"}
	};
	
	outputs(b,2);

	struct Car c[2];

	strcpy(c[0].name,"***");
	c[0].price=888;
	strcpy(c[0].color,"*##");

	strcpy(c[1].name,"***");
	c[1].price=888;
	strcpy(c[1].color,"*##");
	
	outputs(c,2);

	struct Car d[2];
	for (int i = 0; i < 2; i++) {
		scanf("%s",d[i].name);
		scanf("%d",&d[i].price);
		scanf("%s",d[i].color);
	}

	outputs(d,2);
	
	return 0;
}


