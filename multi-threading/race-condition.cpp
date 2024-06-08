/*
    Threads are entities that can be scheduled and executed independently
    by the kernel. Although threads are independent, they share certain resources like
    file descriptors, IPC related (message queues, pipes, shared memory) and other resources  
    of parent process with multiple threads of the same parent process. 
    Manipulating shared resources without an appropriate locking mechanism can lead 
    to race around conditions which can in turn can cause undefined behaviour / security bugs
    such as TOCTOU bugs.  
*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int x = 0;
void * thrFunc(void *){
    for ( int i = 0; i < 10000000; i++ )
    {
        x += 1; 
    }
    cout<<"Value of x after increment op : "<<x<<"\n";
    return NULL;
}

int main(){
    pthread_t thr1,thr2;
    pthread_create(&thr1,NULL,thrFunc,NULL);
    pthread_create(&thr2,NULL,thrFunc,NULL);
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    cout<<"Global data after thread executions : "<<x<<"\n";

}