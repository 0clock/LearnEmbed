#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
        char a[20];
        gets(a);

        int i=0;
        int sum=0;

        while(a[i]==' '){
                i++;
        }

        if(a[i]=='+' || a[i]=='-')
                i++;

        int j=i;

        while(a[j]!='\0'){
                if(a[j] >='0' && a[j]<='9'){
                        sum=sum*10+a[j]-48;
                }else{
                        break;
                }
                j++;
        }

        if(a[i-1]=='-')
                sum=-sum;

        printf("sum=%d\n",sum);

        return 0;
}
