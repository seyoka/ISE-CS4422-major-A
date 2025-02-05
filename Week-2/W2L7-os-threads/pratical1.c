#include <stdio.h>
#include <pthread.h>

struct thr {
    int index;
    pthread_t th ;
};

#define ARRAY_SIZE 8
#define NUMBER_OF_THREADS 2

int results[ARRAY_SIZE];
int arr[ARRAY_SIZE];

void* sum_array(void* arg){
    struct thr * t = (struct thr *) arg ;
    int start = t->index * (ARRAY_SIZE/NUMBER_OF_THREADS);
    int end = start + (ARRAY_SIZE/NUMBER_OF_THREADS);
    int sum = 0;



    for(int i = start; i < end; i++){
        sum += arr[i];
    }
    results[t->index] = sum ;

    printf("\nThread %d computed the sum of %d to %d", t->index, start, end);
    pthread_exit(NULL);
}

int main(){
    struct thr threads[NUMBER_OF_THREADS];
    int *result;

    for(int i = 0; i < ARRAY_SIZE; i++){
        arr[i] = i + 1;
    }

    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        threads[i].index = i ;
        if(pthread_create(&threads[i].th, NULL, sum_array,&threads[i]) != 0){
            perror("Failed to make thread");
            return 1;
        }
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        if (pthread_join(threads[i].th, NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    // Print final results
    printf("\nFinal results array:\n");
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        printf("Thread %d sum: %d\n", i, results[i]);
    }

    return 0;
}
