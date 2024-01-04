/*
 * Filename: 04freadcp.c
 * Author: linus
 * Date: 2024-01-02
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 

#include <stdio.h>

int main(int argc, const char *argv[])
{
	//判断是否输错
	if(argc!=3)
	{
		puts("输入错误！");
		return -1;
	}
	//定义文件指针
	FILE* fp=NULL;
	FILE* fp_cp=NULL;

	//打开文件
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		perror("fopen error:");
		return -1;
	}

	if((fp_cp=fopen(argv[2],"w"))==NULL)
	{
		perror("fopen error:");
		return -1;
	}

	char buff;

	//循环遍历拷贝
	while (1)
	{
		fread(&buff,1,sizeof(buff),fp);
		fwrite(&buff,1,sizeof(buff),fp_cp);
		if(feof(fp))
		{
			break;
		}
	}

	//关闭文件
	fclose(fp);
	fclose(fp_cp);


	return 0;
}
