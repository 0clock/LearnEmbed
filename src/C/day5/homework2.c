#include <stdio.h>

void main(){
	int cock=0,hen=0,small=0;
	while(cock<=100){
		while(hen<=100){
			while(small<=100){
				if((cock*15+hen*9+small)==300 && (cock+hen+small)==100){
					printf("🐓=%d,🐔=%d,🐥=%d\n",cock,hen,small);
					
				}
				small+=3;
			}
			small=0;
			hen++;
		}
		hen=0;
		cock++;
	}
}
