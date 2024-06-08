
/*
    Threads are execution entities that can be scheduled and executed independently
    by the kernel. Multi - threaded applications are incorporated to improve performance 
    and for maximum utilization of multi-cores.
    Additionally, multithreading is less resource-intensive than running multiple processes.  
    A simple mutli-threaded program that manipulates global and static 
    data without involvong any locking mechanism for variables shared between threads. 
*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int g = 0;

void *thrFunc(void *){
    static int s = 0;
    cout<<"In thread, value of global variable : "<<g<<"\n";
    s++;
    cout<<"Static variable value : "<<s<<"\n";
    g++;
    return NULL;
}

int main(){
    pthread_t thr1, thr2,thr3;
    pthread_create(&thr1,NULL,thrFunc,NULL);
    pthread_create(&thr2,NULL,thrFunc,NULL);
    pthread_create(&thr3,NULL,thrFunc,NULL);
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    pthread_join(thr3,NULL);
    cout<<"In main, after thread executions. Value of global variable : "<<g<<"\n";
}