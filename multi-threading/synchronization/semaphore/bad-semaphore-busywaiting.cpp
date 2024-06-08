/*
    Semaphore is a synchronization primitive that enables synchronisation in multi-threaded 
    programming by signaling of events.
    Program demonstrates the basic concept of semaphore.This implementation should be avoided as 
    the semaphore entity itself is not protected and the waiting on semaphore value is a busy 
    wait which wastes CPU cycles that some other process/thread might be able to use productively. 
*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int g_variable = 0;
int semaphore = 1;

void waitSem(int *sem){
    while((*sem) <= 0);
    (*sem)--;
}
void signalSem(int *sem){
    (*sem)++;
}

void *thrFunc(void *){
    waitSem(&semaphore); 
    cout<<"Entering critical section\n";
    g_variable++;
    sleep(3);
    cout<<"Exiting critical section\n";
    signalSem(&semaphore);
    return NULL;
}

int main(){
    pthread_t thr1,thr2,thr3;
    pthread_create(&thr1,NULL,thrFunc,NULL);
    pthread_create(&thr2,NULL,thrFunc,NULL);
    pthread_create(&thr3,NULL,thrFunc,NULL);
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    pthread_join(thr3,NULL);
    cout<<"global variable after thread execution : "<<g_variable<<"\n";

}
