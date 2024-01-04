/*
 * Filename: 05imgpr.c
 * Author: linus
 * Date: 2024-01-02
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
 
#include <stdio.h>

int main(int argc, const char *argv[]){
	FILE *fp=NULL;
	if(NULL==(fp=fopen("./output.bmp","r+")))
	{
		perror("fopen error:");
		return -1;
	}

	//向后偏移两个字节得到文件的大小
	fseek(fp, 0x02, SEEK_SET);
 
	unsigned int size;
	fread(&size, sizeof(size), 1, fp);   //从文件中读取一个整形数据
	printf("size = %d\n", size);


	unsigned int x,y;
	//向后偏移两个字节得到分辨率的大小
	fseek(fp, 0x12, SEEK_SET);	
	fread(&x, sizeof(size), 1, fp);   //从文件中读取一个整形数据
	fread(&y, sizeof(size), 1, fp);   //从文件中读取一个整形数据
	printf("x = %d\ny = %d\n", x,y);


	//将光标偏移到图像数据处
	fseek(fp, 54, SEEK_SET);

	//想要更改像素
	unsigned char color[3] = {255, 0, 0};    //纯蓝色

	for(int i=0; i<800; i++)   //外行
	{
		for(int j=0; j<33; j++)   //内列
		{
			fwrite(color, sizeof(color), 1, fp);
		}
	}
 
	//关闭文件
	fclose(fp);
	
	return 0;
}
