#include <stdio.h>
#include <string.h>
int main(int argc, const char *argv[]){
	char s1[20],s2[20],s3[20];
	
	gets(s1);
	gets(s2);
	gets(s3);
	
	char s1s2=strcmp(s1,s2);
	char s2s3=strcmp(s2,s3);
	char s1s3=strcmp(s1,s3);

	if(s1s2>0&&s1s3>0){
		puts("s1最大\n");
	}else if(s2s3>0&&s1s2<0){		
		puts("s2最大\n");
	}else if(s1s3<0&&s2s3<0){
		puts("s3最大\n");
	}else{
		puts("error!");
	}


	puts(s1);
	return 0;
}
