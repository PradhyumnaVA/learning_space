#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

void move(int,int);

int main(){
	int i,j;
	// pipefd holds the read and write fd(file descriptor)
	int pipefd[2]; 
	char buffer[1];
	pid_t pid;
	int buf_status;

	/// variables for movement ///
	int rand_x,rand_y;
	time_t seed;
	//////
	
	// creating pipe
	if(pipe(pipefd) == -1){
		perror("pipe not created");
		exit(EXIT_FAILURE);
	}

	if(fcntl(pipefd[0], F_SETFL, O_NONBLOCK) < 0){
		exit(2);
	}

	// creating child 
	pid = fork();
	
	if (pid == -1) {
        	perror("fork"); // Handle fork error
		exit(1);
	}

	// clear the screen
//	printf("\033[2J");

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
		exit(0); 
	}

	//parent process
	else {
		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");
		
		// initial position of @
		int x=20;
		int y=5;

		// variable to hold intermediate direction
		char input_dir='d';

		// closing write end of pipe
		close(pipefd[1]); 
		
		while(1){
			// reading from the buffer, read internally clears the buffer
			buf_status = read(pipefd[0], buffer, sizeof(buffer)); 

//			printf("\033[2;1H");
			//printf("buffer=%s\t",buffer);
			//fflush(stdout);
			
			if(buf_status == -1) {
				// if buffer is empty then movement of @ occurs
				if(errno == EAGAIN) {
					switch(input_dir){
						case 'w': y--; break;
						case 's': y++; break;
						case 'a': x=x-2; break;
						case 'd': x=x+2; break;
						default : break;
					}

					move(x,y);
					fflush(stdout);

					usleep(300000);
					printf("\033[2J");
				}
				else {
					perror("read");
					exit(4);
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
	}
	return 0;
}

void move(int x, int y){
    printf("\033[%d;%dH",y,x);
	printf("@");
	printf("\033[2;1Hx=%d,y=%d",x,y);
	fflush(stdout);
//	printf("\033[3:1Hposx=%d,posy=%d,dir=%c",rand_x,rand_y,dir);
}
