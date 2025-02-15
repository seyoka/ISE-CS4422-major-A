#include <stdio.h>
#include <pthread.h>
#include <sys/_pthread/_pthread_cond_t.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int state = 0;

void *waiting_thread(void *arg){
    pthread_mutex_lock(&mutex);

    while(state == 0){
        printf("Thread is waiting for state to change...\n");
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Thread woke up state is now %d. \n", state);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *signaling_thread(void *arg){
    sleep(2);

    pthread_mutex_lock(&mutex);
    state = 1;
    printf("Signaling thread changed to state to %d\n", state);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(){
    pthread_t t1, t2 ;

    pthread_create(&t1, NULL, waiting_thread, NULL);
    pthread_create(&t2, NULL, signaling_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("All threads finished execution. \n");
    return 0;
}
