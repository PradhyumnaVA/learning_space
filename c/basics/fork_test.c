#include <stdio.h>
#include <unistd.h>

int main(){
	int pid,count=0;
	char input_key;
	pid = fork();
	if(pid == 0){
		// child process
		input_key = getchar();
		printf("%c",input_key);
	}
	else {
		// parent process
		while(1){
			printf("@\t");
			fflush(stdout);
			count++;
			sleep(2);
			if(count>5) break;
		}
	}
}
