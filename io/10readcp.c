/*
 * Filename: 10readcp.c
 * Author: linus
 * Date: 2024-01-02
 * Version: 1.0
 *
 * Description: 使用文件io实现拷贝
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    if(argc!=3)
    {
        puts("输入有误");
        return -1;
    }
    int fd=-1,fd_cp=-1;
    fd=open(argv[1],O_RDONLY);
    if(fd==-1)
    {
        perror("打开文件1失败:");
        return -1;
    }
    fd_cp=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0664);
    if(fd_cp==-1)
    {
        perror("打开文件2失败:");
        return -1;
    }
    
    // ssize_t write(int fd, const void *buf, size_t count);
    // 功能：将buf指向的地址中count个字节，写入到fd指向的文件中
    // 参数1：文件描述符
    // 参数2：容器起始地址，void*类型，表明可以写入任何类型的数据
    // 参数3：要写入数据的个数
    // 返回值：成功返回写入的字符个数，失败返回-1并置位错误码

    // ssize_t read(int fd, void *buf, size_t count);
    // 功 能：从fd文件中，将count个字节读取到buf对应的容器中
    // 参数1：文件描述符
    // 参数2：容器起始地址，void*类型，表明可以读取任何类型的数据
    // 参数3：要读取数据的个数
    // 返回值：成功返回读取字节的个数，失败返回-1并置位错误码

    //循环写入
    char buff[4096];
    int res;
    while((res=read(fd,buff,sizeof(buff)))>0)
    {
        write(fd_cp,buff,res);
    }
    //关闭文件
    close(fd);
    close(fd_cp);
}