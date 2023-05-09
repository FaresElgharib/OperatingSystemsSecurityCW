#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "%s: error: %s is not a positive number\n", argv[0], argv[1]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "%s: error: fork failed\n", argv[0]);
        return 1;
    }
    else if (pid == 0) {
        printf("%d", n);
        while (n != 1) {
            if (n % 2 == 0) {
                n = n / 2;
            }
            else {
                n = 3 * n + 1;
            }
            printf(", %d", n);
        }
        printf("\n");
    }
    else {
        wait(NULL);
    }

    return 0;
}