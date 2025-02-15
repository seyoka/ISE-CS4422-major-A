#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>  // Required for O_CREAT flag
#include <sys/stat.h> // Required for permissions
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int count = 0;

sem_t *empty;
sem_t *full;
pthread_mutex_t mutex;

void *producer(void *arg){
    int id = *(int *) arg;

    for(int i = 1; i <= 5; i++){
        sem_wait(empty);  // Wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[count++] = i;
        printf("Producer %d produced: %d\n", id, i);

        pthread_mutex_unlock(&mutex);
        sem_post(full); // Signal that buffer has new item
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg){
    int id = *(int *) arg;

    for(int i = 1; i <= 5; i++){
        sem_wait(full);  // Wait for available item
        pthread_mutex_lock(&mutex);

        int item = buffer[--count];
        printf("Consumer %d consumed: %d\n", id, item);

        pthread_mutex_unlock(&mutex);
        sem_post(empty); // Signal that a slot is available
        sleep(2);
    }
    return NULL;
}

int main(){
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int prod_ids[NUM_PRODUCERS] = {1, 2};
    int cons_ids[NUM_CONSUMERS] = {1, 2};

    // Create named semaphores
    empty = sem_open("/empty_sem", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("/full_sem", O_CREAT, 0644, 0);
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NUM_PRODUCERS; i++){
        pthread_create(&producers[i], NULL, producer, &prod_ids[i]);
    }

    for(int i = 0; i < NUM_CONSUMERS; i++){
        pthread_create(&consumers[i], NULL, consumer, &cons_ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Cleanup
    sem_close(empty);
    sem_close(full);
    sem_unlink("/empty_sem");
    sem_unlink("/full_sem");
    pthread_mutex_destroy(&mutex);

    printf("All producer and consumer threads have finished.\n");
    return 0;
}
