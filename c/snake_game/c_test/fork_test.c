#include <sys/types.h>
#include <stdio.h>

int main(){
	int pid,i,j;
	pid = fork();

	if(pid == 0){
		for(i=0; i<10; i=i+2);
		
		printf("child process: %d\n",i);
	}
	else {
	//	waitpid ( pid, &status, 0 ) ;
		for(j=0; j<11; j++);
		    printf("parent process: %d\n",j);
		
	}
	return 0;
}
