#include "log.h"
#include "time.h"

time_t sys_time;

char *hextochar() {}

void log(char *buf)
{
    //获取时间
    time(&sys_time);
    // printf("sys_time=%ld\n",sys_time);
    struct tm *t = localtime(&sys_time);
    char buff[128] = "";
    sprintf(buff, "[%4d/%02d/%02d-%02d:%02d:%02d]\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    strcat(buff,buf);
    printf("%s", buff);
    
}