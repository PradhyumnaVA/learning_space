#include <stdio.h>
#include <stdlib.h>

int **create_matrix(int rows, int cols, int fill_value) {
	int **matrix = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int *)malloc(cols * sizeof(int));
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = fill_value;
		}
	}
	return matrix;
}

int main() {
	int rows = 5;
	int cols = 4;
	int fill_value = 2;
	int **my_matrix = create_matrix(rows, cols, fill_value);

	// Print the matrix (example)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", my_matrix[i][j]);
		}
		printf("\n");
	}

	// Remember to free the allocated memory when you're done
	for (int i = 0; i < rows; i++) {
		free(my_matrix[i]);
	}
	free(my_matrix);

	return 0;
}

