#include "menu.h"

char *op_msg[]={"添加","删除","修改","查找","退出"};

void print_menu()
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
}
