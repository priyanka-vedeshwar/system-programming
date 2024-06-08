/*
    POSIX Threads aka pthreads are implementation of thread for UNIX systems.
    Threads are entities that can be scheduled and executed independently
    by the kernel but share minimal and essential resources of parent process.
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct thrArg{ 
    int val;
};

void *thrFunc(void *arg){
    sleep(2);
    struct thrArg *value = (struct thrArg *)arg;  
    cout<<"In thread, arg val passed : "<<value->val<< "\n";
    return NULL;
}

int main(){
    pthread_t thr;
    struct thrArg *arg;
    arg->val = 10;
    pthread_create(&thr,NULL,thrFunc,(void *)arg);
    pthread_join(thr,NULL);
    cout<<"In main, after pthread execution\n";
    exit(0);
}