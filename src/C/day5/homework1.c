#include <stdio.h>

void main(){
	printf("请输入行数：");
	int l=0;
	scanf("%d",&l);
	int ll=l,i=0;
	while(l>0){
		while(i<=2*ll-l){
			if(i>=l){
				printf("⏹️");
			}else{
				printf("  ");
			}
			i++;
		}
		printf("\n");
		i=0;
		l--;
	}	
}

