#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

// using struct to hold the variables for coordinates of @ and []
typedef struct {
	int x,y;
	int rand_x, rand_y;
}coord;

/////// functions initialisation /////// 

coord *pos(coord*);
coord *move(coord*, char);

////////////////////////////////////////

int main(){
	// pipefd holds the read and write fd(file descriptor)
	int pipefd[2]; 
	char buffer[1];
	pid_t pid;
	int buf_status;

	// creating pipe
	if(pipe(pipefd) == -1){
		perror("pipe not created");
		exit(EXIT_FAILURE);
	}

	if(fcntl(pipefd[0], F_SETFL, O_NONBLOCK) < 0){
		exit(EXIT_FAILURE);
	}

	// creating child 
	pid = fork();
	
	// process not created
	if (pid == -1) {
        	perror("fork"); // Handle fork error
		exit(EXIT_FAILURE);
	}

	//child process
	if(pid == 0){
		// variable to hold input direction
		char dir; 

		char *write_byte; 
		
		// closing read end of pipe
		close(pipefd[0]); 

		printf("\033[2J");

		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");

		while(1){
			// get input from user for direction
			dir= getchar();
			
			// the input to write needs to be pointer, so user input is turned into pointer
			write_byte = &dir;

		        // write 1 byte of data that is entered 	
			write(pipefd[1], write_byte, 1); 
			
			if(dir == 'q'){
				break; // ends the infinite loop
			}
		}
		
		// change terminal back to normal mode
		system("stty cooked echo");

		// ends the child process, so that it doesnt become zombie
		exit(EXIT_SUCCESS); 
	}

	//parent process
	else {
		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");
		
		// allocate memory on the heap for the present coordinate struct
		coord *present_c = (coord*)malloc(sizeof(coord));

		// initial position of @
		present_c -> x=20;
		present_c -> y=5;

		// variable to hold intermediate direction
		char input_dir='d';

		// closing write end of pipe
		close(pipefd[1]); 
		
		// initial position of []
		present_c=pos(present_c);

		while(1){
			// reading from the buffer, read internally clears the buffer
			buf_status = read(pipefd[0], buffer, sizeof(buffer)); 

			if(buf_status == -1) {
				// if buffer is empty then movement of @ occurs
				if(errno == EAGAIN) {

					printf("\033[%d;%dH", present_c->rand_y, present_c->rand_x);
					printf("[ ]");

					if((present_c->x == present_c->rand_x+1) && (present_c->y == present_c->rand_y)){
						printf("\033[2J");
						printf("\033[1;1Hsuccess\n");
						(present_c->x)++;
						(present_c->y)++;
						present_c = pos(present_c);
						continue;
					}		

					present_c = move(present_c, input_dir);

					usleep(130000);
					printf("\033[2J");
				}
				else {
					perror("read");
					exit(EXIT_FAILURE);
				}
			}

			else {
				input_dir = buffer[0];
				if(input_dir == 'q'){
					break; // ends the infinite loop
				}
			}
		}
		system("stty cooked echo");
		exit(EXIT_SUCCESS);
	}
	return 0;
}

coord *move(coord *ip_coord, char input_dir){
	coord *data = ip_coord;
	
	int x= data -> x;
	int y= data -> y;

	switch(input_dir){
		case 'w': y--; break;
		case 's': y++; break;
		case 'a': x--; break;
		case 'd': x++; break;
		default : break;
	}

	printf("\033[%d;%dH",y,x);
	printf("@");
	printf("\033[2;1Hx=%d,y=%d",x,y);
	printf("\033[3:1Hposx=%d,posy=%d", data -> rand_x, data -> rand_y);
	fflush(stdout);
	
	data -> x = x;
	data -> y = y;

	return data;
}

coord *pos(coord *input_coord){
	// initailise a new struct and give it the value of the struct sent in as argument
	coord *data = input_coord;

	// update the value of the rand coordinates in the new struct
	data -> rand_y= rand() % (20-1 +1) + 4;
	data -> rand_x= rand() % (90-1 +1) + 10;

	// clear the screen
	printf("\033[2J");
	
	// print [] at the rand coordinates
	printf("\033[%d;%dH", data->rand_y, data->rand_x);
	printf("[ ]");
	fflush(stdout);

	// return the data struct, which contains the new rand coordinates, to the main function	
	return data;
}
