#include <stdio.h>

int f1(int x, int y)
{
    return (x & y) + ((x ^ y) >> 1);
}

int f2(int x)
{
    int num = 0;
    while (x)
    {
        num++;
        x = x & (x - 1);
    }

    return num;
}

void main()
{
    printf("f1(354,769)=%d\n", f1(354, 769));
    printf("f2(9475)=%d\n", f2(9475));
}