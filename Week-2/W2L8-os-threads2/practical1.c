#include <stdio.h>
#include <pthread.h>
#include <sys/_pthread/_pthread_t.h>
#include <unistd.h>

static __thread int threadID ;

typedef struct thread{
    int index ;
    pthread_t th;
} thread ;

void* print_t(void * arg ) {
    int t = *(int*) arg ;
    threadID = t * 10;
    printf("\nThread %d is running...", threadID);

    return NULL;
}

thread t[10];

int main(){

    fork();

    for(int i = 0 ; i < 10; i++){
        t[i].index = i;
        pthread_create(&t[i].th, NULL, print_t, &t[i]);
    }


    for(int i = 0; i < 10; i++){
        pthread_join(t[i].th, NULL);
    }

}
