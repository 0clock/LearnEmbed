/*
 * Filename: main.c
 * Author: linus
 * Date: 2023-12-22
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 

#include "myhead.h"

enum Operate{
	Input,
	Output,
	Insert_head,
	Insert_rear,
	Delete_head,
	Delete_rear,
	Insert_pos,
	Delete_pos,
	Update_pos,
	Find_pos,
	Invert,
	Joseph,
	Free_space,
	Exit
};
char *op_msg[]={"Input","Output","头插","尾插",
				"头删","尾删","位置插入","位置删除",
				"位置修改","位置查找","逆置","约瑟夫环","释放","Exit"};
enum Operate op;

int n;


linklist list;

void op_input(){
	printf("请输入初始化链表节点个数：");
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		datatype element;
		printf("请入第%d个节点存储的数据：",i+1);
		scanf("%d",&element);
		list=insert_head(list,element);
	}
	printf("\n\n");
}

void op_Insert_head(){
	datatype element;	
	printf("请入头插的数据：");
	scanf("%d",&element);
	list=insert_head(list,element);
	printf("\n\n");
}

void op_Insert_rear(){
	datatype element;	
	printf("请入尾插的数据：");
	scanf("%d",&element);
	list=insert_rear(list,element);
	printf("\n\n");
}

void op_Delete_head(){
	list=delete_head(list);
	printf("\n\n");
}
void op_Delete_rear(){
	list=delete_rear(list);
	printf("\n\n");
}

void op_Insert_pos(){
	datatype element;
	int pos=0;
	printf("请入头插的位置：");
	scanf("%d",&pos);	
	printf("请入要插的数据：");
	scanf("%d",&element);
	list=insert_pos(list,pos,element);
	printf("\n\n");
}

void op_Delete_pos(){
	int pos=0;
	printf("请入删除的位置：");
	scanf("%d",&pos);	
	list=delete_pos(list,pos);
	printf("\n\n");
}

void op_Update_pos(){
	int pos=0;
	datatype element;
	printf("请入修改的位置：");
	scanf("%d",&pos);	
	printf("请入修改的数据：");
	scanf("%d",&element);
	update_pos(list,pos,element);
	printf("\n\n");
}

void op_Find_pos(){
	int pos=0;
	printf("请入查找的位置：");
	scanf("%d",&pos);	
	printf("\n\n%d号数据为：%d\n\n",pos,find_pos(list,pos));
}

void op_Invert(){
	list=invert(list);
	printf("\n\n");
}

void op_Joseph(){
	int m;
	printf("m=");
	scanf("%d",&m);
	list=joseph(list,n,m);
}
int main(int argc, const char *argv[]){

	while(1){
		for (int i = 0; i <= Exit; i++) {
				printf("【%d】:%s\t",i,op_msg[i]);
				if((i+1)%2==0){
					puts("");
				}
			}
		puts("");	
		printf("请输入要执行的操作：");

		int status;
		status=scanf("%d",&op);
		if(status==0){
			printf("输入错误，请重新输入\n");
			fflush(stdin);
			getchar();
			continue;
		}else if(status==EOF){
			printf("EOF\n");
			continue;
		}


		switch (op) {
			case Input:
				op_input();
				break;
			case Output:
				output(list);
				break;
			case Insert_head:
				op_Insert_head();
				break;
			case Insert_rear:
				op_Insert_rear();
				break;
			case Delete_head:
				op_Delete_head();
				break;
			case Delete_rear:
				op_Delete_rear();
				break;
			case Insert_pos:
				op_Insert_pos();
				break;
			case Delete_pos:
				op_Delete_pos();
				break;
			case Update_pos:
				op_Update_pos();
				break;
			case Find_pos:
				op_Find_pos();
				break;
			case Invert:
				op_Invert();
				break;
			case Free_space:
				free_space(list);
				break;
			case Joseph:
				op_Joseph();
				break;
			case Exit:
				return 0;
			default:
				puts("error!");
		}
	}
		
	return 0;
}
