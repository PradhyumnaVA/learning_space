#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void new_matrix(int width, int height, int indent){
	int i,j;
	char *up = (char*)malloc(width+indent+1);
	char *down = (char*)malloc(width+indent+10);

	for (int j = 0; j < width + indent; j++) {
		up[j] = '-';
	}
	/* printf("%s ",up); */

	strcat(down,"\033[10;1H");
	strcat(down,up);

	char *left = malloc(50);

	strcat(left,"\033[2;1H");
	
	for(i=0;i<3;i++){
		left[i] = '|';
		/* strcat(left,"\n"); */
	}

	printf("%s %s",up,down);
	printf(" %s",left);
}

char **create_matrix(int width, int height, int indent){
	
	int i,j;

	char **matrix = (char **)malloc(height * (sizeof(char*)));

	for(i=0; i< height; i++){
		matrix[i] = (char *)malloc((width+indent+1) * sizeof(char));
		for (int j = 0; j < width + indent; j++) {
			matrix[i][j] = ' ';
		}
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

int main() {
	int width = 100;  // Width of the box
	int height = 20; // Height of the box
	int indent = 5; // Number of spaces for indentation
		
	/* char **box = create_matrix(width,height,indent); */
	/* char *str = malloc(height*(width+indent+1)); */
	/* char *row = malloc(width+indent+1); */

	int i;
	system("clear");
	// Print the box
	/* for (i = 0; i < height; i++) { */
	/* 	sprintf(row, "%s\n", box[i]); */
	/* 	strcat(str,row); */
	/* } */

/* void new_matrix(int width, int height, int indent){ */
	new_matrix(width,height,indent);
	/* printf("\033[4;1H%s",str); */
	return 0;
}

