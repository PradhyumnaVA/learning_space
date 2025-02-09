#include <stdio.h>

int main() {
    int rows, cols, i, j;
	rows=10;
	cols=100;

    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= cols; j++) {
            if (i == 1 || i == rows) {
                printf("-");
            } else if (j == 1 || j == cols) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}

