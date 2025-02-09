#include <stdio.h>
#include <stdlib.h>

int main() {
	int width = 100;  // Width of the box
	int height = 20; // Height of the box
	int indent = 5; // Number of spaces for indentation

	// Create a 2D array to represent the box
	char box[height][width + indent + 1]; // +1 for null terminator, if you were to treat each row as a string

	// Fill the array with spaces
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width + indent; j++) {
			box[i][j] = ' ';
		}
		box[i][width + indent] = '\0'; // Null terminate each row
	}

	// Draw the top and bottom borders
	for (int j = indent; j < width + indent; j++) {
		box[0][j] = '-';
		box[height - 1][j] = '-';
	}

	// Draw the side borders
	for (int i = 1; i < height - 1; i++) {
		box[i][indent] = '|';
		box[i][width + indent - 1] = '|';
	}

	system("clear");
	// Print the box
	printf("\033[3;1H");
	for (int i = 0; i < height; i++) {
		printf("%s\n", box[i]);
	}

	return 0;
}

