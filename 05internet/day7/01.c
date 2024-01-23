#include "header.h"
#include "menu.h"
#include <sqlite3.h>

int do_search_table(sqlite3 *ppDb)
{
	char sql[128] = "select * from Worker";
	char **res_ptr = NULL;
	int rows = 0;
	int cols = 0;
	char *errmsg = NULL;
	if (sqlite3_get_table(ppDb, sql, &res_ptr, &rows, &cols, &errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec error:%s", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}

	for(int i=0;i<rows+1;i++)
	{
		for(int j=0;j<cols;j++)
		{
			printf("%10s",*(res_ptr+(i*cols+j)));
		}
		printf("\n");
	}
	sqlite3_free_table(res_ptr);
	return 0;
}

int callback(void *arg, int cols, char **value_text, char **value_name)
{
	if ((*(int *)arg) == 0)
	{
		for (int i = 0; i < cols; i++)
		{
			printf("%10s", value_name[i]);
		}
		printf("\n");
		*((int *)arg) = 1;
	}
	for (int i = 0; i < cols; i++)
	{
		printf("%10s", value_text[i]);
	}
	printf("\n");
	return 0;
}

int do_search(sqlite3 *ppDb)
{
	int flag = 0;
	char sql[128] = "select* from Worker";
	char *errmsg = NULL;

	if (sqlite3_exec(ppDb, sql, callback, &flag, &errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec error:%s", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
	return 0;
}

int do_add(sqlite3 *ppDb)
{
	int add_uid; // 学号
	char add_name[20];
	char add_sex[10];
	double add_score;

	printf("学号：");
	scanf("%d", &add_uid);
	printf("姓名：");
	scanf("%s", add_name);
	printf("性别：");
	scanf("%s", add_sex);
	printf("成绩");
	scanf("%lf", &add_score);
	getchar();

	char sql[128] = "";
	sprintf(sql, "insert into Worker(uid,name,sex,score) values(%d,\"%s\",\"%s\",%lf);", add_uid, add_name, add_sex, add_score);
	printf("sql=%s\n", sql);

	char *errmsg = NULL;
	if (sqlite3_exec(ppDb, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exe error:%s\n", errmsg);
		sqlite3_free(errmsg);
		errmsg = NULL;
		return -1;
	}
	printf("增加成功\n");
	return 0;
}

int main(int argc, const char *argv[])
{
	// 1、打开或创建数据库
	sqlite3 *ppDb = NULL;
	if (sqlite3_open("./worker.db", &ppDb) != SQLITE_OK)
	{
		printf("sqlite3_open error,errcode = %d, errmsg = %s\n", sqlite3_errcode(ppDb), sqlite3_errmsg(ppDb));
		return -1;
	}
	printf("sqlite3_open success\n");

	// 2、数据库相关操作
	// 2.1 创建数据表
	// 准备sql语句
	// char *sql = "create table if not exists Worker(numb int, name char, sex char, score double);";
	char sql[128] = "create table if not exists Worker(uid int, name char, sex char, score double);";
	char *errmsg = NULL; // 记录返回的错误信息
	// 执行sql语句
	if (sqlite3_exec(ppDb, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec error: %s\n", errmsg);
		// 释放errmsg的空间
		sqlite3_free(errmsg);
		errmsg = NULL;
		return -1;
	}
	printf("create table success\n");

	while (1)
	{
		print_menu();

		enum Operate op;
		scanf("%d", &op);

		switch (op)
		{
		case ADD:
			do_add(ppDb);
			break;
		case UPDATE:
			// do_ipdate();
			break;
		case SEARCH:
			// do_search(ppDb);
			do_search_table(ppDb);
			break;
		case EXIT:
			return 0;
		default:
			break;
		}
	}
	return 0;
}