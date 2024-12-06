#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 6
#define TCOUNT 10
#define COUNT_LIMIT 120

int count = 0;

pthread_mutex_t count_mutex;
pthread_cond_t count_threshold;

void* inc_count(void* t);
void* watch_count(void* t);

int main(void) {
    long t1 = 1, t2 = 2, t3 = 3;

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold, NULL);
    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&threads[0], &attr, watch_count, (void*) t1);
    pthread_create(&threads[1], &attr, inc_count, (void*) t2);
    pthread_create(&threads[2], &attr, inc_count, (void*) t3);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("[Main] > Waited and joined with %d threads. Final value of count = %d. DONE.\n", NUM_THREADS, count);

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold);
    pthread_exit(NULL);
}

void* inc_count(void* t) {
    long thread_id = (long) t;

    for (int i = 0; i < TCOUNT; i++) {
        pthread_mutex_lock(&count_mutex);
        count++;

        if (count == COUNT_LIMIT) {
            printf("[Incrementer](%ld) > count = %d Threshold reached.\n", thread_id, count);
            pthread_cond_signal(&count_threshold);
            printf("[Incrementer](%ld) > Threshold signal sent.\n", thread_id);
        }
        printf("[Incrementer](%ld) > count = %d, unlocking mutex\n", thread_id, count);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }

    pthread_exit(NULL);
}

void* watch_count(void* t) {
    long thread_id = (long) t;
    printf("[Watcher] > watching thread %ld\n", thread_id);

    pthread_mutex_lock(&count_mutex);
    while (count < COUNT_LIMIT) {
        printf("[Watcher](%ld) > count = %d. Going into wait...\n", thread_id, count);
        pthread_cond_wait(&count_threshold, &count_mutex);
        printf("[Watcher](%ld) > condition signal received. Count = %d\n", thread_id, count);
        printf("[Watcher](%ld) > updating the value of count...\n", thread_id);
        count += 125;
        printf("[Watcher](%ld) > count now = %d\n", thread_id, count);
    }

    printf("[Watcher](%ld) > unlocking mutex.\n", thread_id);
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}