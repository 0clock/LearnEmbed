#include <stdio.h>

#define MAX 255

int main()
{
    unsigned char A[MAX],i;
    A[255]=12;
    for ( i = 0; i <= MAX; i++)
    {
        A[i]=i;
        printf("i=%d\n",i);
    }
    
}