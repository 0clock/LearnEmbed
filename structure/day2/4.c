/*
 * Filename: 4.c
 * Author: linus
 * Date: 2023-12-20
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

struct Car{
	char name[10];
	int price;
};

void outputs(struct Car *p){
	printf("品牌\t单价\n");
	printf("%s\t%d\n",p->name,p->price);
}

void outputs_arr(struct Car *p){
	for (int i = 0; i < 2; i++) {
		printf("%s\t%d\n",(p+i)->name,(p+i)->price);
		printf("%s\t%d\n",(*(p+i)).name,(*(p+i)).price);
	}
}



int main(int argc,const char *argv[]){
	struct Car a={"GIANT",2200};

	outputs(&a);

	struct Car b[2]={"凤凰",250,"小刀",2000};
	outputs_arr(b);

	return 0;
}


