/*
 * Filename: main.c
 * Author: linus
 * Date: 2023-12-21
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 

#include "myhead.h"
int main(int argc, const char *argv[]){
	sqlist* list=creat_list();

	int n;
	scanf("%d",&n);
	datatype element;
	for (int i =0 ; i < n; i++) {
		printf("Please Enter %d Element:",i+1);
		scanf("%d",&element);
		int flag=insert_rear(list,element);
		if(flag==FALSE){
			puts("NULL || FULL");
			break;
		}
	}
	//delete_rear(list);
	output(list);
	int index;
	/*
	printf("查找元素：");
	scanf("%d",&index);
	search_index(list,index);
	
	printf("修改元素：");
	scanf("%d",&index);
	scanf("%d",&element);
	update_index(list,index,element);
	output(list);
	
	printf("插入元素：");
	printf("位置：");
	scanf("%d",&index);
	printf("元素：");
	scanf("%d",&element);
	insert_index(list,index,element);
	output(list);
	
	printf("删除元素：");
	scanf("%d",&index);
	delete_index(list,index);
	output(list);
*/
	
	/////////////////////////////////
	datatype key;
	printf("要查找的元素：");
	scanf("%d",&key);
	int in=search_key(list,key);
	if(in==FALSE){
		printf("没有找到。\n");
	}else{
		printf("in %d\n",in);
	}
	
	/////////////////////////////////
	printf("要删除的元素：");
	scanf("%d",&key);
	
	if(delete_key(list,key)){
		printf("没有找到,删除失败。\n");
	}else{
		printf("删除成功");
	}
	output(list);
	
	////////////////////////////////
	datatype new;
	printf("要修改前的元素：");
	scanf("%d",&key);
	printf("要修改后的元素：");
	scanf("%d",&new);
	change_key(list,key,new);	
	output(list);
	
	///////////////////////////////
	printf("去重\n");
	deduplicate(list);
	output(list);

	//////////////////////////////
	printf("排序\n");
	sort(list);
	output(list);

	my_free(list);
	return 0;
}
