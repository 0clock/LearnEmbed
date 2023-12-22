#include <stdio.h>

void main(){
	int n;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	
	for(int i=1;i<n;i++){
		int count = 0;
		for(int j=0;j<n-i;j++){
			if(arr[j]<arr[j+1]){
				count++;
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
			if(count=0){
				break;
			}
		}
	}
	printf("降序：");
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}	

