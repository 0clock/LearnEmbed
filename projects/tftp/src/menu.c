#include "menu.h"

char *op_msg[]={"发送","下载","Exit"};

void print_menu()
{
    for (int i = 0; i <= Exit; i++)
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
