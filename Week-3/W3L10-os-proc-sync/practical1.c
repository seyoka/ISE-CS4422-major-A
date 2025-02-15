#include <stdio.h>
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>

pthread_mutex_t lock;
int counter = 0;

void *increment(void *arg){

    pthread_mutex_lock(&lock);

    counter++;


    printf("Thread %lu incremented counter to %d\n",(unsigned long) pthread_self(), counter);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    pthread_t t1, t2 ;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);
}
