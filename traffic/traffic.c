//
// Created by msgh on 6/12/24.
//

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>
#include <semaphore.h>
#include <pthread.h>
#include "key_logger.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

int pass = 0;// 0 -> north, 1 -> east, 2 -> south, 3 -> west, else pedestrian
static sem_t sem;
static sem_t ped_sem;
bool pedestrian_request;

void log_traffic(int pass) {
    switch (pass) {
        case 0: printf("%snorth%s\teast\tsouth\twest\n", GREEN, RED); break;
        case 1: printf("%snorth%s\teast%s\tsouth\twest\n", RED, GREEN, RED); break;
        case 2: printf("%snorth\teast\t%ssouth%s\twest\n", RED, GREEN, RED); break;
        case 3: printf("%snorth\teast\tsouth\t%swest\n", RED, GREEN); break;
        default: printf("%snorth\teast\tsouth\twest\n",  RED);
    }
    usleep(1000000); // 1000 mili seconds
}

void *simulate_traffic() {
    while (true) {
        log_traffic(pass);
        sem_wait(&sem);
        pass = (pass+1) % 4;
        sem_post(&sem);
    }
}

void *pedestrian_handler() {
    while (true) {
        sem_wait(&ped_sem);
        if(pedestrian_request == true) {
            sem_wait(&sem);
            log_traffic(4);
            sem_post(&sem);
            pedestrian_request = false;
        }
        sem_post(&ped_sem);
        usleep(1000000);
    }
}

void check_pedestrians(char c) {
    if (c == 'f') {
        sem_wait(&ped_sem);
        pedestrian_request = true;
        sem_post(&ped_sem);
    }
}

int main() {
    sem_init(&sem, 0, 1);
    sem_init(&ped_sem, 0, 1);

    pthread_t traffic_thread;
    pthread_t pedestrians_thread;

    pthread_create(&traffic_thread, NULL, simulate_traffic, NULL);
    pthread_create(&pedestrians_thread, NULL, pedestrian_handler, NULL);
    pthread_t thread_id = start_listening(check_pedestrians);

    pthread_join(traffic_thread, NULL);
    pthread_join(thread_id, NULL);
    pthread_join(pedestrians_thread, NULL);

    sem_destroy(&sem);
    sem_destroy(&ped_sem);

    return 0;
}