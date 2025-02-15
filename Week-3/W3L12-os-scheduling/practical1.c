#include <mach/arm/kern_return.h>
#include <mach/kern_return.h>
#include <mach/mach_types.h>
#include <mach/thread_act.h>
#include <mach/thread_policy.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mach/mach.h>
#include <unistd.h>
#include <sys/sysctl.h>


void set_thread_affinity(int core_id){
    thread_port_t thread = mach_thread_self();
    thread_affinity_policy_data_t policy = {core_id};

    kern_return_t result = thread_policy_set(thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, 1);

    if(result != KERN_SUCCESS){
        fprintf(stderr, "Failed to set thread affinity\n");
    }else{
        printf("Thread affinity set to core %d\n", core_id);
    }
}

void* thread_function(void* arg){
    int core_id = *(int*)arg;
    set_thread_affinity(core_id);

    for (int i = 0; i < 5; i++) {
        printf("Running on core %d - Iteration %d\n", core_id, i);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thread;
    int core_id = 2; // Prefer core 2

    /* Create a thread and set its affinity */
    if (pthread_create(&thread, NULL, thread_function, &core_id) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    /* Wait for the thread to finish */
    pthread_join(thread, NULL);

    int num_cores;
    size_t len = sizeof(num_cores);

    // Get the number of physical CPU cores
    if (sysctlbyname("hw.physicalcpu", &num_cores, &len, NULL, 0) == 0) {
        printf("Physical CPU Cores: %d\n", num_cores);
    } else {
        perror("sysctl hw.physicalcpu");
    }

    // Get the number of logical CPU cores (includes hyper-threading)
    if (sysctlbyname("hw.logicalcpu", &num_cores, &len, NULL, 0) == 0) {
        printf("Logical CPU Cores: %d\n", num_cores);
    } else {
        perror("sysctl hw.logicalcpu");
    }

    return 0;

    return 0;
}
