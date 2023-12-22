#include <stdio.h>
#include <string.h>
int main(int argc, const char *argv[]){
	char s1[20],s2[20],temp[20];
	
	gets(s1);
	gets(s2);

	strcpy(temp,s1);
	strcpy(s1,s2);
	strcpy(s2,temp);

	printf("s1=%s\n",s1);
	printf("s2=%s\n",s2);
	return 0;
}
