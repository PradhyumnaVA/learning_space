#include <stdio.h>

int main() {
    int c;

    printf("Enter characters (Ctrl+D to end):\n");
    while ((c = getchar()) != EOF) {
        putchar(c); // Echoes back the character
    }

    return 0;
}

