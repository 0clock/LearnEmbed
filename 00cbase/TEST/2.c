/*
 * Filename: 2.c
 * Author: linus
 * Date: 2023-12-12
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include <stdio.h>

int main(int argc, const char *argv[])
{
	// int *a(int x)[10];
	// int (*a[10])(int);
	// 置一
	unsigned char num = 0x00;
	num |= (1 << 1);
	printf("num=%d\n", num);

	for (int i = 0; i < 8; i++)
	{
		unsigned char bit = 0, n;
		n = num >> i;
		bit = n & 0x01;
		printf("bit%d= %d\n", i, bit);
	}

	return 0;
}
