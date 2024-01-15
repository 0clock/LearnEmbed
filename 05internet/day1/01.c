/*
 * Filename: 01.c
 * Author: linus
 * Date: 2024-01-12
 * Version: 1.0
 *
 * Description: 判断是大端存储还是小端存储
 */


#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, const char *argv[])
{
	int num=0x12345678;
	char *p=(char*)&num;
	if(*p==0x12)
	{
		printf("大端\n");
	}else if(*p==0x78){
		printf("小端\n");
	}

	unsigned int num1 = 0x12345678;
	unsigned short int key = 0x1234;

	printf("num1的字节网络节序值为：%#x\n",htonl(num1));
	printf("key的字节网络节序值为：%#x\n",htons(key));


	return 0;
}
