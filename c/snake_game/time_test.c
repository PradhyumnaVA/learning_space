// using this code to test the clock speed of system 

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	//char c = '@';
	int i,count=0;
	while(1){
		printf("@\t");
		fflush(stdout);
		count++;
		sleep(1);
		if(count > 5) break;
	}
	return 0;
}
