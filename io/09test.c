/*
 * Filename: 09test.c
 * Author: linus
 * Date: 2024-01-02
 * Version: 1.0
 *
 * Description: 重复使用菜单框架
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Operate
{
	REGISTER,
	LOGIN,
	EXIT
};
char *op_msg[] = {"注册", "登录", "退出"};

enum Operate menu;

int do_register()
{
	FILE *wfp =NULL;
	char username_reg[20];
	char pwd_reg[20];

	printf("请输入账号：");
	fgets(username_reg,sizeof(username_reg),stdin);
	printf("请输入密码：");
	fgets(pwd_reg,sizeof(pwd_reg),stdin);

	username_reg[strlen(username_reg)-1]='\0';
	pwd_reg[strlen(pwd_reg)-1]='\0';

	if((wfp=fopen("./user.txt","a+"))==NULL)
	{
		perror("open user.txt error:");
		return -1;
	}

	fprintf(wfp,"%s %s\n",username_reg,pwd_reg);
	fclose(wfp);
	printf("注册成功!\n");

	return 0;
}

int do_login()
{
	FILE *wfp =NULL;
	char input_username[20];
	char input_pwd[20];

	char username_reg[20];
	char pwd_reg[20];

	printf("请输入账号：");
	fgets(input_username,sizeof(input_username),stdin);
	printf("请输入密码：");
	fgets(input_pwd,sizeof(input_pwd),stdin);

	input_username[strlen(input_username)-1]='\0';
	input_pwd[strlen(input_pwd)-1]='\0';

	if((wfp=fopen("./user.txt","r"))==NULL)
	{
		perror("open user.txt error:");
		return -1;
	}

	while(1)
	{
		int res = fscanf(wfp,"%s %s",username_reg,pwd_reg);
		if (res<0)
		{
			printf("没有这个用户\n");
			fclose(wfp);
			return 1;
		}

		if(strcmp(username_reg,input_username)==0 && strcmp(pwd_reg,input_pwd)==0){
			printf("登录成功！\n");
			fclose(wfp);
			return 0;
		}
		
	}

}

int main(int argc, const char *argv[])
{
	while (1)
	{
		for (int i = 0; i <= EXIT; i++)
		{
			printf("【%d】:%s\t", i, op_msg[i]);
			if ((i + 1) % 2 == 0)
			{
				puts("");
			}
		}
		puts("");
		printf("请输入要执行的操作：");
		scanf("%d", &menu);
		while (getchar() != '\n'); // 吸收非法字符
		switch (menu)
		{
		case REGISTER:
			do_register();
			break;
		case LOGIN:
			do_login();
			break;
		case EXIT:
			exit(EXIT_SUCCESS);
		default:
			printf("输入序号有误，请重新输入:");
		}
		printf("按任意键清屏\n");
		while (getchar() != '\n'); // 吸收非法字符
		system("clear");
	}

	return 0;
}
