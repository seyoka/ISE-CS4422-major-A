#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

struct thr {
    int index;
    pthread_t th;
};

void* print_thread(void* arg){
    struct thr * t = (struct thr *) arg;

    while(1){
        printf("\nThread %d is running... ", t->index);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    struct thr threads[10];

    for(int i = 0; i < 10; i++){
        threads[i].index = i ;
        pthread_create(&threads[i].th, NULL, print_thread, &threads[i]);
    }

    for(int i = 0; i < 10; i++){
        pthread_join(threads[i].th, NULL);
    }
}
