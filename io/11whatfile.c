/*
 * Filename: 11whatfile.c
 * Author: linus
 * Date: 2024-01-03
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
	//定义文件属性类型的数据
	struct stat sb;      //用于存储获得的文件属性
 
	//调用函数的到文件属性
	stat(argv[1], &sb);
 
	switch(sb.st_mode&S_IFMT)
	{
	case S_IFSOCK:
		{
			printf("这是套接字文件\t");
		}
		break;
	case S_IFLNK:
		{
			printf("这是链接文件\t");
		}
		break;
	case S_IFREG:
		{
			printf("这是普通文件\t");
		}
		break;
	case S_IFBLK:
		{
			printf("这是块设备文件\t");
		}
		break;
	case S_IFDIR:
		{
			printf("这是目录文件\t");
		}
		break;
	case S_IFCHR:
		{
			printf("这是字符设备文件\t");
		}
		break;
	case S_IFIFO:
		{
			printf("这是管道文件\t");
		}
		break;
 
	}
 
	printf("%#o\t%ld\t%ld\n", sb.st_mode&0777, sb.st_size, sb.st_ino);
 
	return 0;
}