#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct q5 {
    int *fib_seq;
    int n;
} fib_data;

void *generate_fibonacci(void *arg) {
    fib_data *data = (fib_data *)arg;
    int *fib_seq = data->fib_seq;
    int n = data->n;

    fib_seq[0] = 0;
    fib_seq[1] = 1;

    for (int i = 2; i < n; i++) {
        fib_seq[i] = fib_seq[i-1] + fib_seq[i-2];

    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <number of fibonacci nums\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1) {
        fprintf(stderr, "Number of Fibonacci numbers must be larger than 0\n");
        return 1;
    }

    int *fib_seq = (int *)malloc(n * sizeof(int));
    if (fib_seq == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    pthread_t fib_thread;
    fib_data data = {fib_seq, n};
    if (pthread_create(&fib_thread, NULL, generate_fibonacci, &data) != 0) {
        fprintf(stderr, "Thread creation error\n");
        return 1;
    }

    if (pthread_join(fib_thread, NULL) != 0) {
        fprintf(stderr, "thread join error\n");
        return 1;
    }

    printf("Fibonacci Sequence\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib_seq[i]);
    }

    printf("\n");

    free(fib_seq);

    return 0;
}