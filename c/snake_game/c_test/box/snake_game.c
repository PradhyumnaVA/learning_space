#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// using struct to hold the variables for coordinates of @ and []
typedef struct {
	int x,y;
	int rand_x, rand_y;
}coord;

/////// functions initialisation /////// 

coord *pos(coord*);
coord *move(coord*, char);
char* keep_score(char*, int);
char** create_matrix(int, int, int);

////////////////////////////////////////

int main(){
	// pipefd holds the read and write fd(file descriptor)
	int pipefd[2]; 
	char buffer[1];
	pid_t pid;
	int buf_status;

	int width = 100;  // Width of the box
	int height = 20; // Height of the box
	int indent = 5; // Number of spaces for indentation

	int i;

	char *mark = malloc(10);
	mark = "--------";

	char **box = create_matrix(width,height,indent);
	char *str = malloc(height*(width+indent+1));
	char *row = malloc(width+indent+1);

	// Print the box
	for (i = 0; i < height; i++) {
		sprintf(row, "%s", box[i]);
		strcat(str,row);
		strcat(str,"\n");
	}
					printf("\033[4;1H%s",str);
					sleep(5);

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

		char *score = (char*)malloc(20*sizeof(char)); 
		int count=0;

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
				// if buffer is empty then movement of snake head occurs
				if(errno == EAGAIN) {
					printf("\033[4;50H%s",mark);
					printf("\033[4;1H%s",str);

					printf("\033[%d;%dH", present_c->rand_y, present_c->rand_x);
					printf("[ ]");

					if((present_c->x == present_c->rand_x+1) && (present_c->y == present_c->rand_y)){
						printf("\033[2J");
						printf("\033[1;1Hsuccess\n");
						(present_c->x)++;
						(present_c->y)++;
						count++;
						score = keep_score(score,count);			
						present_c = pos(present_c);
						continue;
					}		

					printf("\033[1;1H");
					printf("%s%d", score, count*10);
					fflush(stdout);

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
		free(present_c);	
		free(score);
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

	switch(input_dir){
		case 'w': printf("^"); break;
		case 's': printf("v"); break;
		case 'a': printf("<"); break;
		case 'd': printf(">"); break;
		default : break;
	}

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

char* keep_score(char *input, int i){
	char *foo = (char*)malloc(20*sizeof(char)); 
	foo = input;

	strcat(foo, "#");
	printf("\033[1;1H");
	printf("%s%d", foo, i*10);
	fflush(stdout);

	return foo;
}

char **create_matrix(int width, int height, int indent){
	
	int i,j;

	char **matrix = (char **)malloc(height * (sizeof(char*)));

	for(i=0; i< height; i++){
		matrix[i] = (char *)malloc((width+indent+1) * sizeof(char));
		/* for (int j = 0; j < width + indent; j++) { */
		/* 	matrix[i][j] = ' '; */
		/* } */
		matrix[i][width + indent] = '\0'; // Null terminate each row
	}

	// Draw the top and bottom borders
	for (int j = indent; j < width + indent; j++) {
		matrix[0][j] = '-';
		matrix[height - 1][j] = '-';
	}

	// Draw the side borders
	for (int i = 1; i < height - 1; i++) {
		matrix[i][indent] = '|';
		matrix[i][width + indent - 1] = '|';
	}

	return matrix;
}

/* int main() { */
/* 	int width = 100;  // Width of the box */
/* 	int height = 20; // Height of the box */
/* 	int indent = 5; // Number of spaces for indentation */
		
/* 	char **box = create_matrix(width,height,indent); */

/* 	int i; */
/* 	system("clear"); */
/* 	// Print the box */
/* 	printf("\033[3;1H"); */
/* 	for (i = 0; i < height; i++) { */
/* 		printf("%s\n", box[i]); */
/* 	} */
/* 	return 0; */
/* } */

