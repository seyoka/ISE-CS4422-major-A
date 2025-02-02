#include <signal.h>
#include <stdio.h>

void hande_signit(int sig){
    printf("Caught signal %d\n", sig);
}

int main(){

    while (1) {
        signal(SIGINT, hande_signit);
    }
}
