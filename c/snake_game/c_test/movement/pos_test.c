#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// using struct to hold the variables for coordinates of @ and []
typedef struct {
	int x,y;
	int rand_x, rand_y;
}coord;

// pos function takes in the coordinate struct and return is also of the same form
coord *pos(coord*);

int i;

int main(){
	pid_t pid;

	// Seed with current time to get different random sequences
	srand(time(NULL));
	
	// fork to get 2 processes
	pid = fork();

	// child process
	if(pid == 0){
		// allocate memory on the heap for the present coordinate struct
		coord *present_c = (coord*)malloc(sizeof(coord));

		system("clear");
		// Generate random number
		int random_number;

		for(i=0; i<10; i++){
			// the present coordinates are updated with the rand coordinates from the function
			present_c = pos(present_c);

			// wait for 1 second
			sleep(1);
		}
		free(present_c);
	}

	// parent process
	else{
		while(1){
			printf("\033[1;1H");
			printf("parent process");
			fflush(stdout);
			usleep(30000);
		}
	}
	return(0);
}

coord *pos(coord *input_coord){
	// initailise a new struct and give it the value of the struct sent in as argument
	coord *data = input_coord;

	int x = data->rand_x;

	// update the value of the rand coordinates in the new struct
	data -> rand_y= rand() % (20-3 +1) + 3;
	data -> rand_x= rand() % (100-1 +1) + 1;

	system("clear");
	
	// print [] at the rand coordinates
	printf("\033[%d;%dH", data->rand_y, data->rand_x);
	printf("[ ]%d",x);
	fflush(stdout);

	// return the data struct, which contains the new rand coordinates, to the main function	
	return data;
}
