#include <stdio.h>

void main(){
	int n;
    scanf("%d",&n);
    int arr[n],max,max2;
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
	
	max=arr[0];
	
	for(int i=0;i<n;i++){
		if(max<arr[i]){
			max=arr[i];
		}

	}

	max2=arr[0];

	for(int i=0;i<n;i++){
        if(max2 < arr[i] && max2 < max){
            max2=arr[i];
        }

    }	

	printf("最大值为：%d\n",max);
	printf("第二大值为：%d\n",max2);
}
