/*
 * Filename: 03time.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

time_t sys_time = 0;
char time_buff[128] = ""; // 写入文件的字符串
struct tm *t;
int line = 1;

int get_time()
{
	time(&sys_time);
	t = localtime(&sys_time);
	sprintf(time_buff, "%4d[%4d/%02d/%02d-%02d:%02d:%02d]\n", line,
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	return t->tm_sec;
}

int main(int argc, const char *argv[])
{

	FILE *fp = NULL;
	int last_sec = -1;

	if ((fp = fopen("./time.txt", "r")) == NULL)
	{
		perror("打开文件失败：");
		// return -1;
	}

	// 先读出文件有多少行
	char buff[128];
	while (NULL != fgets(buff, sizeof(buff), fp))
	{
		line++;
	}

	while (1)
	{
		// a:以结尾写的形式打开文件，如果文件不存在，则创建文件，如果文件存在则结尾写，光标定位在开结尾
		if ((fp = fopen("./time.txt", "a")) == NULL)
		{
			perror("打开文件失败：");
			return -1;
		}
		sleep(1);

		// 每秒才写入
		if (last_sec != get_time())
		{
			last_sec = t->tm_sec;
			fputs(time_buff, fp);
			line++;
		}
		printf("%d\n", line);
		fclose(fp);
	}

	return 0;
}
