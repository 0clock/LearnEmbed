#include <stdio.h>

void main(){
	printf("请输入一个数：");
	int n,sum=0;
	scanf("%d",&n);
	

	for(int i=1;i<n;i++){
		if(n%i==0){
			sum=sum+i;
		}
	}
	if(sum==n){
		printf("是完数\n");
	}else{
		printf("不是完数\n");
	}
		
}
