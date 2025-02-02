#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_SIGSEGV(int sig){
    printf("Caught Seg Fault (signal %d) and now exiting the program", sig);
    exit(1);
}

int main(){
    signal(SIGSEGV, handle_SIGSEGV);
    int *p = NULL;

    *p = 42;
}
