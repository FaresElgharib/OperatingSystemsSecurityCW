#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 256

int main(int argc, char *argv[]) {

    int pipefd[2];
    pid_t pid;
    char buf[BUF_SIZE];
    int count_chars = 0;
    int count_words = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *source = fopen(argv[1], "r");
    if (!source) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);

        while (read(pipefd[0], buf, BUF_SIZE) > 0) {
            count_chars += strlen(buf);
            char *tok = strtok(buf, " \n");
            while(tok) {
                count_words++;
                tok = strtok(NULL, " \n");
            }
        }

        close(pipefd[0]);

        FILE *dest = fopen(argv[2], "w");
        if (!dest) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        fprintf(dest, "Count of characters: %d\nCount of words: %d", count_chars,count_words);
        fclose(dest);

        exit(EXIT_SUCCESS);
    }
    else {
        close(pipefd[0]);

        while (fgets(buf, BUF_SIZE, source) != NULL) {
            write(pipefd[1], buf, strlen(buf));
        }

        close(pipefd[1]);

        wait(NULL);

        fclose(source);

        exit(EXIT_SUCCESS);
    }
}