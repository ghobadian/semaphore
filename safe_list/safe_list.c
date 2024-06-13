#include <malloc.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *array;
    sem_t *locks;       //for each cell we have a lock
    int size;
    int capacity;
} ArrayList;

static ArrayList* list;
static sem_t append_lock;   //a lock for when we want to append to our list, no other thread can append with us

ArrayList* create_arraylist() {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->capacity = INITIAL_CAPACITY;
    list->array = malloc(INITIAL_CAPACITY * sizeof(int));
    list->locks = malloc(INITIAL_CAPACITY * sizeof(sem_t));
    for (int i = 0; i < list->capacity; ++i) {
        sem_init(&list->locks[i], 0, 1);
    }
    list->size = 0;
    return list;
}

void read(ArrayList* list, int index) {
    printf("reading from index:%d of list with size:%d with value:%d\n", index, list->size, list->array[index]);//nothing is changed, so no lock
}

void safe_write(ArrayList* list, int index, int value) {
    sem_wait(&list->locks[index]);
    printf("writing value:%d to index:%d in list with size:%d\n", value, index, list->size);
    list->array[index] = value;
    sem_post(&list->locks[index]);
}

void safe_append(ArrayList* list, int value) {
    sem_wait(&append_lock);
    printf("appending value:%d to list with size:%d\n", value, list->size);
    int last_index = list->size;
    list->array[last_index] = value;
    list->size++;
    if(list->size == list->capacity) {
        list->capacity += INITIAL_CAPACITY;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
        list->locks = (sem_t*)realloc(list->array, list->capacity * sizeof(sem_t));
        for (int i = list->size; i < list->capacity; ++i) {
            sem_init(&list->locks[i],0, 1);
        }

    }
    sem_post(&append_lock);
}

void length(ArrayList* list) {
    printf("length of list:%d\n", list->size); //nothing is changed, so no lock
}

void delete(ArrayList* list) {
    for (int i = 0; i < list->capacity; ++i) {
        sem_destroy(&list->locks[i]);
    }
    free(list->array);
    free(list);
}

void delete_cell(ArrayList* list, int index) {
    printf("deleting cell with index:%d", index);
    list->array[index] = -1;
}

void* thread_1_playing_with_array() {
    safe_append(list, 4);
    safe_write(list, 0, 9);
    read(list, 0);
}

void* thread_2_playing_with_array() {
    safe_append(list, 8);
    safe_write(list, 0, 65);
}

void* thread_3_playing_with_array() {
    safe_append(list, 14);
    length(list);
}

void experiment() {
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    pthread_create(&thread1, NULL, thread_1_playing_with_array, NULL);
    pthread_create(&thread2, NULL, thread_2_playing_with_array, NULL);
    pthread_create(&thread3, NULL, thread_3_playing_with_array, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);


}


int main() {
    sem_init(&append_lock, 0, 1);
    list = create_arraylist();

    experiment(list);

    sem_destroy(&append_lock);
    delete(list);
    return 0;
}

