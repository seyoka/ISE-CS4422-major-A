#include <stdatomic.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/_pthread/_pthread_t.h>
#include <unistd.h>

atomic_flag spinlock = ATOMIC_FLAG_INIT;
int counter = 0;

void *increment(void *arg){

    printf("Thread %lu trying to acquire spinlock..\n", (unsigned long) pthread_self());

    while(atomic_flag_test_and_set(&spinlock));

    printf("Thread %lu acquired the spinlock!\n", (unsigned long) pthread_self());

    counter++;
    printf("Thread %lu incremented counter to %d\n", (unsigned long) pthread_self(), counter);

    sleep(10);
    atomic_flag_clear(&spinlock);
    printf("Thread %lu released spinlock.\n", (unsigned long) pthread_self());
    return NULL;

}

int main(){
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    sleep(1);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);
    return 0;
}
