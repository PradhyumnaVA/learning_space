#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(){
	int i,j;
	// pipefd holds the read and write fd(file descriptor)
	int pipefd[2]; 
	char usr_input;
	char buffer[1];
	pid_t pid;
	int buf_status;

	// creating pipe
	if(pipe(pipefd) == -1){
		perror("pipe not created");
		exit(EXIT_FAILURE);
	}

	if(fcntl(pipefd[0], F_SETFL, O_NONBLOCK) < 0)
		exit(2);

	// creating child 
	pid = fork();
	
	if (pid == -1) {
        	perror("fork"); // Handle fork error
		exit(1);
	}

	if(pid == 0){
		//child process

		printf("\033[2J");
		
		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");
		while(1){
			// closing read end of pipe
			close(pipefd[0]); 
			usr_input = getchar();
			
			// the input to write needs to be pointer, so user input is turned into pointer
			char *write_byte = &usr_input;

		        // write 1 byte of data that is entered 	
			write(pipefd[1], write_byte, 1); 

			// move cursor to top-left corner
			printf("\033[H");

			printf("child sent: %c\n",usr_input);
			fflush(stdout);
			if(usr_input == 'q'){
				break; // ends the infinite loop
			}
		}
		// change terminal back to normal mode
		system("stty cooked echo");
		exit(0); // ends the child process, so that it doesnt become zombie
	}
	else {
	 	//parent process
		// change the terminal to raw mode, input directly taken, no need to press ENTER
		system("stty raw -echo");
		
		// for position of @
		int x=0;

		// clear the terminal screen
		printf("\033[2J");
		close(pipefd[1]); // closing write end of pipe
		
		while(1){
			// reading from the buffer, read internally clears the buffer
			buf_status = read(pipefd[0], buffer, sizeof(buffer)); 
			
			if(buf_status == -1) {
				if(errno == EAGAIN) {
					// printf("\033[2J");
					printf("\033[10;%dH",x++);
					printf("@");
					fflush(stdout);
					usleep(500000);
					// break;
				}
				else {
					perror("read");
					exit(4);
				}
			}
			else {
				// printf("\033[4;1H %ld", sizeof(buffer));
				
				// move cursor to starting point of 5th line
				printf("\033[5;1H");

				printf("parent received: %s\n", buffer);
				fflush(stdout);
			
				if(buffer[0] == 'q'){
					break; // ends the infinite loop
				}
			}
		}
		system("stty cooked echo");
	}
	return 0;
}
