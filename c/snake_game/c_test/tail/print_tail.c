#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(){
//	char *foo = (char*)malloc(20*sizeof(char)); 
	char foo[5];
	char *ptr = foo;
	int i;

	system("clear");

	for(i=0;i<4;i++){
		strcat(foo, "#\033[B\033[1D");
		//printf("\033[%d;10H",i);
		//printf("%c%d", *(ptr++), i*10);
		//fflush(stdout);
		//sleep(1);
	}
	strcat(foo, "v");

	for(i=0;i<10;i++){
		printf("\033[%d;10H",i+5);
		printf("%s",foo);
		fflush(stdout);
		sleep(1);
		system("clear");
	}

/*
	char p[]= "v \nv \nv \n";
	printf("\033[1;10H%s",p);
//	printf("\033[1;10Hhello \n world\n");
*/
	return EXIT_SUCCESS;
}
