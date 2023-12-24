#include <stdio.h>
#include <stdbool.h>
void main(){
	int len;
	scanf("%d",&len);	
	int arr[len];
	for(int i=0;i<len;i++){
		scanf("%d",&arr[i]);
	}

	int prime_count=0;
	bool isPrime=true;
	for(int i=0;i<len;i++){
		//判断是不是素数
		if(arr[i]<2){
			continue;
		}
		
		for(int j=2;j*j<=arr[i];j++){
			if(arr[i]%j==0){
				isPrime=false;
				break;//不是素数
			}else{
				isPrime=true;
			}
				
		}

		if(isPrime){
			prime_count++;
		}
		
	}

	printf("有%d个素数\n",prime_count);
}
