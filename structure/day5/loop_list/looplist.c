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
 * function:    链表的创建
 * @param [ in
 * @param [out] 
 * @return      
 */
linklist creat_node(){
	linklist p=(linklist)malloc(sizeof(struct Node));
	if(NULL == p)
		return NULL;
	p->data=0;
	p->next=p;
	return p;
}

/*
 * function:    链表的头插
 * @param [ in
 * @param [out] 
 * @return      
 */
linklist insert_head(linklist head,datatype element){
	linklist s= creat_node();
	if(NULL==s)
		return head;
	s->data=element;

	if (NULL==head) {
		head=s;
		return head;
	}
	//找到最后一个节点

	linklist rear=head;
	while(rear->next!=head){
		rear=rear->next;
	}
	// s的指针域
	s->next=head;
	head=s;
	// 实现单项循环链表
	rear->next=head;
	return head;
}

/*
 * function:    output
 * @param [ in] linklist
 * @param [out] printf linklist
 * @return      void
 */
void output(linklist head){
	linklist temp=head;
	printf("\n\n----------链表---------\n");
	printf("序号\tdata\tlinklist\n");
	int i=0;

	do{
		printf("%d\t",++i);
		printf("%d\t",temp->data);
		printf("%p\n",temp);
		temp=temp->next;
	}while(temp!=head);

	puts("-----------------------");
	printf("\n\n");
}

/*
 * function:    尾插
 * @param [ in] 
 * @param [out] 
 * @return      
 */
linklist insert_rear(linklist head,datatype element){
	linklist p=creat_node();
	if(NULL==p){
		return head;
	}
	p->data=element;

	if(NULL==head){
		head=p;
	}else{
		linklist temp=head;
		while(temp->next!=head){
			temp=temp->next;
		}
		temp->next=p;
		p->next=head;
	}
	return head;
}

/*
 * function:    头删
 * @param [ in] list
 * @param [out] 
 * @return      
 */
linklist delete_head(linklist head){
	if(NULL==head)
		return head;
	// 如果存在节点=1
	if(head==head->next){
		free(head);
		head=NULL;
		return NULL;
	}

	// 找到最后一个节点,为了删掉头节点时候能找到
	linklist p = head;
	while (p->next != head){
		p=p->next;
	}

	linklist del=head;
	head=head->next;
	free(del);
	del=NULL;
	p->next=head;
	return head;
}

/*
 * function:    尾删
 * @param [ in] 
 * @param [out] 
 * @return      
 */
linklist delete_rear(linklist head){
	if(NULL==head)
		return NULL;
	// 只有一个节点
	if(head->next==head){
		free(head);
		head=NULL;
		return head;
	}else{//多个节点
		linklist p=head;
		while(p->next->next!=head){
			p=p->next;
		}
		free(p->next);
		p->next=head;
	}

	return head;
}

/*
 * function:    计算linklist长度
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int len_linklist(linklist head){
	int count=0;
	linklist temp=head;
	do{
		temp=temp->next;
		count++;
	}while(temp!=head);

	return count;
}


/*
 * function:    任意位置插入
 * @param [ in] 
 * @param [out] 
 * @return      头
 */
linklist insert_pos(linklist list,int pos,datatype element){
	if(pos<1 || pos>len_linklist(list)+1){
		return list;
	}
	if(pos==1){
		return insert_head(list,element);
	}

	linklist p=list;
	for (int i = 1; i < pos-1; i++) {
		p=p->next;
	}

	linklist s=creat_node();
	if(NULL==s)
		return list;
	s->data=element;

	s->next=p->next;
	p->next=s;
	return list;
}


/*
 * function:    位置删除
 * @param [ in] 
 * @param [out] 
 * @return      
 */
linklist delete_pos(linklist list,int pos){
	if(NULL==list||pos<1 || pos>len_linklist(list)){
		return list;
	}

	if(pos==1){
		return delete_head(list);
	}

	linklist p = list;
	for (int i = 1; i < pos-1; i++) {
		p=p->next;
	}
	
	linklist del=p->next;
	p->next=del->next;
	free(del);
	del=NULL;
	return list;
}


/*
 * function:    位置查找
 * @param [ in] list,pos
 * @param [out] 
 * @return      data 0 
 */
datatype find_pos(linklist list,int pos){
	if(NULL==list||pos<1||pos>len_linklist(list)){
		return error;
	}
	linklist p=list;
	for (int i = 1; i < pos; i++) {
		p=p-> next;
	}

	return p->data;
}

/*
 * function:    位置修改
 * @param [ in] list,pos,element
 * @param [out] 
 * @return      
 */
void update_pos(linklist list,int pos,datatype element){
	if(NULL==list||pos<1||pos>len_linklist(list)){
		return;
	}
	linklist p=list;
	for (int i = 1; i < pos; i++) {
		p=p->next;
	}
	p->data=element;
}

/*
 * function:    单向链表逆置
 * @param [ in] list
 * @param [out] 
 * @return      list
 */
linklist invert(linklist list){
	if(NULL==list || NULL==list->next)
		return list;
	linklist p=list->next;
	list->next=NULL;
	while(p!=NULL){
		linklist temp=p;
		p=p->next;
		temp->next=list;
		list=temp;
		//p=p->next;
		//printf("p=%p\n",p);
	}
	return list;
}

/*
 * function:    单向链表排序
 * @param [ in] 
 * @param [out] 
 * @return      
 */
linklist sort(linklist list){
	if(NULL==list || NULL==list->next)
		return list;

}

/*
 * function:    单向链表任意元素查找
 * @param [ in] 
 * @param [out] 
 * @return      
 */
linklist search_element(linklist list,datatype element){
			
}

/*
 * function:    释放
 * @param [ in] 
 * @param [out] 
 * @return      
 */

linklist free_space(linklist head){
	if(NULL==head)
		return head;

	linklist p=head;
	while(p!=NULL){
		p=delete_head(p);
	}
	head=NULL;
	return head;
}

/*
 * function:    约瑟夫环
 * @param [ in
 * @param [out] 
 * @return      
 */
linklist joseph(linklist head,int n,int m){
	// if(NULL==head)
	// 	return head;
	// linklist p=head;

	// for(int i=0;i<n;i++){
	// 	for(int j=0;j<m-2;j++){
	// 		p=p->next;
	// 	}
	// 	linklist del=p->next;
	// 	printf("%d\t",del->data);
	// 	p->next=del->next;
	// 	free(del);
	// 	del=NULL;
	// 	p=p->next;
	// }
	// return p;
}
