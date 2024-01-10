#include <stdio.h>
#include <string.h>

int main(int argc,const char *argv[])
{
    char buf[128];
    fgets(buf,sizeof(buf),stdin);
    printf("sizeof(buf)=%ld\n",sizeof(buf));
    fputs(buf,stdout);
    printf("strlen=%ld\n",strlen(buf));
    fputs(buf,stdout);
    return 0;
}