#include <stdio.h>
#include <stdlib.h>

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
		
	char **box = create_matrix(width,height,indent);

	int i;
	system("clear");
	// Print the box
	printf("\033[3;1H");
	for (i = 0; i < height; i++) {
		printf("%s\n", box[i]);
	}
	return 0;
}

