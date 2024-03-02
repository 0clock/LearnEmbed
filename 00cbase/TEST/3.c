/*
 * Filename: 3.c
 * Author: linus
 * Date: 2023-12-11
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include <stdio.h>

typedef union
{
    long i;
    int k[4];
    char c;
} DATE;

struct data
{
    int cat;
    DATE cow;
    double dog;
} too;

DATE max;

int count_voca(const char *str)
{
    int i = 0;
    while (*(str + i) == ' ')
    {
        i++;
    }
    int count = 0;
    while (*(str + i) != '\0')
    {
        if (*(str + i) >= 'A' && *(str + i) <= 'Z' || *(str + i) >= 'a' && *(str + i) <= 'z')
        {
            if (*(str + i + 1) <= 'A' && *(str + i + 1) >= 'z')
                count++;
        }
        i++;
    }
    return count;
}

int main(int argc, const char *argv[])
{
    printf("count = %d\n", count_voca("   lalalla,vskfvs ,fdsgsd ,sdg, dsfg ds, ds,gdsfg, sdfsg,s dfgdsfg, sdg ,, dfg,."));
    printf("count = %d\n", count_voca("HELLO"));
}