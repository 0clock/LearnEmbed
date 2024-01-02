/*
 * Filename: test.c
 * Author: linus
 * Date: 2023-12-22
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include "myhead.h"
/*
 * function:    创建节点
 * @param [ in]
 * @param [out] 
 * @return      
 */
doublelink creat_node(){
	doublelink p=(doublelink)malloc(sizeof(struct Node));
	if(NULL==p)
		return NULL;
	p->data='\0';
	p->next=NULL;
	p->priv=NULL;
	return p;
}

/*
 * function:    双向链表的创建
 * @param [ in]
 * @param [out] 
 * @return      
 */
doublelink insert_head(doublelink head,datatype element){
	doublelink s=creat_node(head);
	if(s==NULL)
		return NULL;
	s->data=element;
	
	if(head->next==NULL){
		head=s;
	}else{
		s->next=head;
		head->priv=s;
		head=s;
	}

	return head;
}

/*
 * function:    双向链表的输出
 * @param [ in]
 * @param [out] 
 * @return      
 */
void output(doublelink head){
	if(NULL==head){
		return;
	}
	doublelink p=head;
	while(p->next)
}