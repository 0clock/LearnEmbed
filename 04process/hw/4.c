/*
 * Filename: 4.c
 * Author: linus
 * Date: 2024-01-05
 * Version: 1.0
 *
 * Description: 使用三个线程完成：线程1输出字符’A’,线程2输出字符’B’,
 *				线程3输出字符’C’,
 *				要求输出结果为：
 *				ABCABCABCABCABC…
 */
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

int main(int argc, const char *argv[])
{
	
	return 0;
}
