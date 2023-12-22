/*
 * Filename: test.c
 * Author: linus
 * Date: 2023-12-21
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include "myhead.h"

/*
 * function:顺序表堆区申请内存    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
sqlist* creat_list(){
	sqlist* list=(sqlist*)malloc(sizeof(sqlist));
	if(NULL==list){
		return NULL;
	}
	memset(list->data,0,sizeof(list->data));
	list->len=0;
	return list;
}


/*
 * function:    判满
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int isFull(sqlist* list){
	return list->len==MAXSIZE?FALSE:SUCCESS;
}

/*
 * function:    尾插入
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int insert_rear(sqlist* list,datatype element){
	if(NULL==list || isFull(list))
		return FALSE;
	list->data[list->len]=element;
	list->len++;
	return SUCCESS;
}

/*
 * function:    判断为空
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int isEmpty(sqlist* list){
	return list->len==0?FALSE:SUCCESS;
}

/*
 * function:    输出
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int output(sqlist *list){
	if(NULL==list||isEmpty(list))
		return FALSE;
	for (int i = 0; i < list->len; i++) {
		printf("%d\t",list->data[i]);
	}
	puts("");
	return SUCCESS;
}

/*
 * function:    尾删
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int delete_rear(sqlist* list){
	if(NULL==list || isEmpty(list))
		return FALSE;
	list->len--;
	return SUCCESS;
}

/*
 * function:    按下标查找
 * @param [ in] 
 * @param [out] 
 * @return      
 */

void search_index(sqlist* list,int index){
	if(NULL==list || isEmpty(list) || index<0 || index>=list->len)
		return;
	printf("search by index element is %d\n",list->data[index]);
}

/*
 * function:    修改
 * @param [ in] 
 * @param [out] 
 * @return      
 */

void update_index(sqlist* list,int index,datatype element){ 
	if(NULL==list || isEmpty(list) || index<0 || index>=list->len)
		return;
	list->data[index]=element;
}

/*
 * function:    插入
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int insert_index(sqlist* list,int index,datatype element){
	if(NULL==list || isFull(list) || index<0 || index>list->len)
		return FALSE;
	for (int i = list->len-1; i >= index; i--) {
		list->data[i+1]=list->data[i];
	}
	list->data[index]=element;
	list->len++;
	return SUCCESS;
}

/*
 * function:    删除
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int delete_index(sqlist* list,int index){
	if(NULL==list || isEmpty(list) || index<0 || index>=list->len)
		return FALSE;
	for (int i=index+1;i< list->len ;i++) {
		list->data[i-1]=list->data[i];
	}
	list->len--;
	return SUCCESS;

}

/*
 * function:    按元素查找
 * @param [ in] list,key
 * @param [out] 元素下标
 * @return      
 */

int search_key(sqlist* list,datatype key){
	int in=-1;
	if(NULL==list || isEmpty(list))
		return FALSE;
	for (int i = 0; i < list->len; i++) {
		if(list->data[i]==key){
			in=i;
			break;
		}
	}
	if(in==-1){
		return FALSE;
	}else{
		return in;
	}
}

/*
 * function:    顺序表按元素删除(如果存在重复则只能删除第一个)
 * @param [ in] 
 * @param [out] 
 * @return      
 */

int delete_key(sqlist* list,datatype key){
	int in=search_key(list,key);
	
	if(in==FALSE)
		return FALSE;

	return delete_index(list,in);
}

/*
 * function:    顺序表按元素修改
 * @param [ in] 
 * @param [out] 
 * @return      
 */

int change_key(sqlist* list,datatype key,datatype new){
	int in=search_key(list,key);
	
	if(in==FALSE)
		return FALSE;

	update_index(list,in,new);
	return SUCCESS;

}


/*
 * function:    顺序表去重
 * @param [ in] list
 * @param [out] 
 * @return      
 */
int deduplicate(sqlist* list){
	for (int i = 0; i < list->len-1; i++) {
		for (int j = i+1; j <= list->len-i; j++) {
			if(list->data[i]==list->data[j]){
				delete_index(list,j);
				j--;
			}
		}
	}
	return SUCCESS;
}

/*
 * function:    13 顺序表排序
 * @param [ in] list
 * @param [out] 
 * @return      
 */
int sort(sqlist* list){
	if(NULL==list || isEmpty(list))
		return FALSE;
	
	for (int i = 0; i < list->len-1; i++) {
		for (int j = 0; j < list->len-i-1; j++) {
			if(list->data[j] > list->data[j+1]){
				datatype temp=list->data[j];
				list->data[j]=list->data[j+1];
				list->data[j+1]=temp;
			}
		}
	}
	return SUCCESS;
}
/*
 * function:    顺序表释放
 * @param [ in] list
 * @param [out] 
 * @return      
 */

sqlist* my_free(sqlist* list){
	if(NULL==list || isEmpty(list))
		return NULL;
	free(list);
	list=NULL;
	return list;
}
