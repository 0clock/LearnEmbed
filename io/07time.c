/*
 * Filename: 07time.c
 * Author: linus
 * Date: 2023-12-29
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */
#include <stdio.h>
#include <time.h>

time_t sys_time;

int main(int argc, const char *argv[]){
	time(&sys_time);
	//printf("sys_time=%ld\n",sys_time);
	struct tm *t=localtime(&sys_time);
	char buff[128]="";
	

	sprintf(buff,"[%4d/%02d/%02d-%02d:%02d:%02d]\n",\
	t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	printf("%s",buff);
	return 0;
}
