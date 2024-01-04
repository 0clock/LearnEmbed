#include <stdio.h>
int main(int argc, const char *argv[])
{
    int year;
    scanf("%d",&year);
    if(year%4==0&&year%100!=0||year%400==0)
    {
        printf("%d是一个闰年\n",year);
	if(year%400==0){
	    printf("%d年是一个超级闰年\n",year);
	}
    }
    else
    {
        printf("%d是平年\n",year);
    }
    return 0;
}
