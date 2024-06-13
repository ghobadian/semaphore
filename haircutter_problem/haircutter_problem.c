#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t sem;
int n = 10;


void *cut_hair(void *input) {
    int i = (int) input;
    int sleep_time = rand() % 5;

    printf("%d: sleeping for %d\n", i, sleep_time);
    sleep(sleep_time);

    sem_wait(&sem);
    printf("%ld: Let's get this haircut\n", i);
    sleep(5);

    printf("%d: I like ya cut G\n", i);
    sem_post(&sem);
}

int main() {
    pthread_t *tid = malloc( n * sizeof(pthread_t) );
    sem_init(&sem, 0, 5);
    for (int i = 0; i < n; ++i) {
        pthread_create(&tid[i], NULL, cut_hair, i);
    }

    for (int i = 0; i < n; ++i) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&sem);
    free(tid);

    return 0;
}