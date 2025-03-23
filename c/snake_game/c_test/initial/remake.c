#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int x=20;
int y=5;
int rand_x,rand_y;
time_t seed;
char dir; 

void move(char);
void pos(void);
int kbhit(void);

void *blob_movement(void *arg){
	// char dir = *((char *) arg);
	// int count=0;
	while(1){
		// system("clear");	
		// usleep(90000);
		system("clear");	
		printf("\033[%d;%dH@",y,x);
		//printf("@");
		switch(dir){
			case 'w': y--; break;
			case 's': y++; break;
			case 'a': x--; break;
			case 'd': x++; break;
			default : break;
		}
		// printf("%d",count);
		// count++;	
		if(dir=='q'){
			// printf("exit");
			break;
		}
		sleep(2);	
	}
}

int main() {
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, blob_movement, NULL);

	printf("\033[2J");
	system("stty raw -echo");
	//char dir;
	time(&seed);
	pos();
	srand(seed);
	//printf("r");
	//dir=getchar();
	//printf("%c",dir);
	//while ((dir = getchar()) != 'c') {	
	//printf("\e[1;1H\e[2J");
	for(;;){
		if((x==rand_x+1) && y==rand_y){
			printf("\e[1;1H\e[2J");
			printf("hh");
			printf("\033[1;1Hsuccess\n");
			x++;y++;
			pos();
			continue;
		}		
		
		dir=getchar();

		if(dir=='q'){
			printf("exit");
			break;
		}		
				
		printf("%c",dir);
		// printf("\e[1;1H\e[2J");
        // printf("\033[2J\033[H");
        system("clear");
		//pos();
		printf("\033[%d;%dH",rand_y,rand_x);
 	    printf("[ ]");
		move(dir);
	}
	system("stty -raw echo");
	// pthread_join(thread_id, NULL);
return 0;
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

// function to generate the random position of the brackets
void pos(){
	//srand(seed);
	rand_y= rand()% (20-3 +1) + 3;
	rand_x= rand() %(100-1 +1) + 1;

	system("clear");
	printf("\033[%d;%dH",rand_y,rand_x);
	printf("[ ]");
}
