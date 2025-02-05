#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Structure to hold thread information
struct thr {
    pthread_t th; // Thread identifier
    int index;    // Thread index
};

// Array to store thread information
struct thr t[10];

// Function to be executed by each thread
void *func(void *arg) {
    // Cast argument to struct thr* and access its index
    struct thr *t = (struct thr *)arg;
    printf("Thread %d running...\n", t->index);
    sleep(10); // Simulate some work with a 10-second sleep
    return NULL; // Return NULL as no value is needed
}

int main() {
    // Create threads
    for (int i = 0; i < 10; i++) {
        t[i].index = i; // Assign thread index
        pthread_create(&t[i].th, NULL, func, &t[i]); // Create thread
    }

    // Wait for all threads to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(t[i].th, NULL); // Join thread
    }

    return 0; // Program completed successfully
}
