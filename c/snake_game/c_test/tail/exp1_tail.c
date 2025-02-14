#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	char bone[9];
} tail;

int main(){
	int len_tail =7;

	tail *foo = (tail*)malloc(len_tail*sizeof(tail)); 

	// tail configurations
	char t_down[] = "#\033[A\033[D";
	char t_right[] = "#\033[2D"; 
	char t_up[] = "#\033[B\033[D";
	char t_left[] = "#"; 

	// head configurations
	char h_down[] = "v\033[A\033[D"; 
	char h_right[] = ">\033[2D"; 
	char h_up[] = "^\033[B\033[D"; 
	char h_left[] = "<";

	int i;
	int p_x,p_y;

	system("clear");

	// downward movement
	for (i = 0; i < 10 ; i++) {
		if(i<len_tail){
			if(i==0){
				strcpy(foo[i].bone, h_down);
			}
			else{
				strcpy(foo[i].bone, t_down);
			}
		}

		printf("\033[%d;10H", i + 5);

		// Print all bone strings
		for (int j = 0; j < len_tail; j++) {
		    printf("%s", foo[j].bone);
		}
		fflush(stdout);
		usleep(300000);
		printf("\033[H\033[J"); // Clear screen and move cursor to top-left
		p_y=i+5;
	}

	// right movement
	for (i = 0; i < 20; i++) {
		if(i<len_tail){
			if(i==0){
				strcpy(foo[i].bone, h_right);
			}
			else{
				strcpy(foo[i].bone, t_right);
			}
		}

		printf("\033[%d;%dH",p_y,i+10);

		// Print all bone strings
		for (int j = 0; j < len_tail; j++) {
		    printf("%s", foo[j].bone);
		}
		fflush(stdout);
		usleep(300000);
		printf("\033[H\033[J"); // Clear screen and move cursor to top-left
		p_x=i+10;
	}

	// upward movement
	for (i = 0; i < 10; i++) {
		if(i<len_tail){
			if(i==0){
				strcpy(foo[i].bone, h_up);
			}
			else{
				strcpy(foo[i].bone, t_up);
			}
		}

		printf("\033[%d;%dH",(p_y-i),p_x);

		// Print all bone strings
		for (int j = 0; j < len_tail; j++) {
		    printf("%s", foo[j].bone);
		}
		fflush(stdout);
		usleep(300000);
		printf("\033[H\033[J"); // Clear screen and move cursor to top-left
	}

	p_y=p_y-10;

	// left movement
	for (i = 0; i < 20; i++) {
		if(i<len_tail){
			if(i==0){
				strcpy(foo[i].bone, h_left);
			}
			else{
				strcpy(foo[i].bone, t_left);
			}
		}

		printf("\033[%d;%dH",p_y,(p_x-i));

		// Print all bone strings
		for (int j = 0; j < len_tail; j++) {
		    printf("%s", foo[j].bone);
		}
		fflush(stdout);
		usleep(300000);
		printf("\033[H\033[J"); // Clear screen and move cursor to top-left
	}
	return EXIT_SUCCESS;
}
