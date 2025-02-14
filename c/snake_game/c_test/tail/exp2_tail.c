#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	char bone[9];
} tail;

tail *print_bone(int len_tail, tail *foo, char dir, int i){
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

	char t_dir[9], h_dir[9];

	switch(dir){
		case 's': strcpy(t_dir,t_down); 
			  strcpy(h_dir,h_down);
			  break;
		default: break;
	}

	if(i<len_tail){
		if(i==0){
			strcpy(foo[i].bone, h_dir);
		}
		else{
			strcpy(foo[i].bone, t_dir);
		}
	}

	printf("\033[%d;10H", i + 5);

	for (int j = 0; j < len_tail; j++) {
	    printf("%s", foo[j].bone);
	}

	fflush(stdout);
	usleep(300000);
	printf("\033[H\033[J");

	return foo;
}

int main(){
	int len_tail=5;
	tail *foo = (tail*)malloc(len_tail*sizeof(tail)); 

	char dir;
	int j;

	for(j=0; j<15; j++){
		if(j<6){
			dir='s';
			foo = print_bone(len_tail,foo,dir,j);
		}
		else{
			dir='d';
			foo = print_bone(len_tail,foo,dir,j);
		}
	}

	return EXIT_SUCCESS;
}
