#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char bone[9]; // Increased size to accommodate null terminator
} tail;

int main() {
    tail *foo = (tail*)malloc(5 * sizeof(tail));
    int i;
    const char escape_sequence[] = "#\033[B\033[D";

    if (foo == NULL) {
        perror("malloc failed");
        return EXIT_FAILURE;
    }

    //system("clear"); // Clear screen once at the beginning

    // Initialize the bone arrays with the escape sequence
    for (i = 0; i < 4; i++) {
        strncpy(foo[i].bone, escape_sequence, sizeof(foo[i].bone) - 1);
        foo[i].bone[sizeof(foo[i].bone) - 1] = '\0'; // Ensure null termination
    }

    // Assign "v" to the last bone array
    strncpy(foo[4].bone, "v", sizeof(foo[4].bone) - 1);
    foo[4].bone[sizeof(foo[4].bone) - 1] = '\0'; // Ensure null termination

    for (i = 0; i < 10; i++) {
        printf("\033[%d;10H", i + 5);

        // Print all bone strings
        for (int j = 0; j < 5; j++) {
            printf("%s", foo[j].bone);
        }
        fflush(stdout);
        sleep(1);
        printf("\033[H\033[J"); // Clear screen and move cursor to top-left
    }

    free(foo); // Free the allocated memory
    return EXIT_SUCCESS;
}

