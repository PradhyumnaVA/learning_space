#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

/// variables for movement ///
int x=20;
int y=5;
int rand_x,rand_y;
time_t seed;
char dir; 
//////

void move(char);

int main(){
	system("stty raw -echo");
	while(1){
		system("clear");
		dir=getchar();
		if(dir=='q'){
			printf("exit");
			break;
		}		
		move(dir);
	}
	system("stty cooked echo");
	return(0);
}

void move(char dir){
	switch(dir){
		case 'w': y--; break;
		case 's': y++; break;
		case 'a': x--; break;
		case 'd': x++; break;
		default : break;
	}
    
    printf("\033[%d;%dH",y,x);
	printf("@");
	printf("\033[2;1Hx=%d,y=%d",x,y);
	printf("\033[3:1Hposx=%d,posy=%d,dir=%c",rand_x,rand_y,dir);
}
