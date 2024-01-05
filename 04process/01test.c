/*
 * Filename: errno.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: 创建出三个进程完成两个文件之间拷贝工作，
 *              子进程1拷贝前一半内容，子进程2拷贝后一半内容，
 *              父进程回收子进程的资源
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    // 判断输入是否正确
    if (argc != 3)
    {
        puts("输入有误！");
        return -1;
    }
    // 定义文件指针
    FILE *fp = 0;
    FILE *fp_cp = 0;
    // 以只读的形式打开文件
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        perror("fopen:");
        return -1;
    }

    // 以只写的形式打开文件
    if ((fp_cp = fopen(argv[2], "w")) == NULL)
    {
        perror("fopen:");
        return -1;
    }

    // 读文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    long half_size = file_size / 2;
    rewind(fp);

    // 创建出一个子进程
    pid_t pid1 = fork();
    if (pid1 == 0) // 子进程1
    {
        char buff;
        while (ftell(fp) < half_size)
        {
            int res = fread(&buff, 1, sizeof(buff), fp);
            fwrite(&buff, 1, res, fp_cp);
        }

        exit(EXIT_SUCCESS);
    }
    else if (pid1 == -1)
    {
        perror("fork error");
        return -1;
    }

    // 创建出另一个子进程
    pid_t pid2 = fork();
    if (pid2 == 0) // 子进程2
    {
        char buff;
        fseek(fp, half_size, SEEK_SET);
        fseek(fp_cp, half_size, SEEK_SET);
        while (!feof(fp))
        {
            int res = fread(&buff, 1, sizeof(buff), fp);
            fwrite(&buff, 1, res, fp_cp);
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid1 == -1)
    {
        perror("fork error");
        return -1;
    }

    wait(NULL);
    wait(NULL);

    fclose(fp);
    fclose(fp_cp);

    return 0;
}
