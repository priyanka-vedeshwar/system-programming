/*
  Semaphore is a synchronization primitive that enables synchronisation in multi-threaded 
  programming by signaling of events.
  Program demonstrates implementation of semaphore using mutex and conditional variable.
*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int g_variable = 0;

typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int value;
}semaphore;

void semaphore_init(semaphore *sem, int val){
    pthread_mutex_init(&(sem->mutex),NULL);
    pthread_cond_init(&(sem->cond),NULL);
    sem->value = val;
}

void semaphore_wait(semaphore *sem ){
  pthread_mutex_lock(&(sem->mutex));
  while (sem->value <= 0) {
        pthread_cond_wait(&(sem->cond), &(sem->mutex));
    }
    sem->value--;
    pthread_mutex_unlock(&(sem->mutex));
}

void semaphore_signal(semaphore* sem) {
    pthread_mutex_lock(&(sem->mutex));
    sem->value++;
    pthread_cond_signal(&(sem->cond));
    pthread_mutex_unlock(&(sem->mutex));
}

void *thrFunc(void *arg){
    semaphore *sem = (semaphore*)arg;    
    semaphore_wait(sem); 
    cout<<"Entering critical section\n";
    g_variable++;
    sleep(3);
    cout<<"Exiting critical section\n";
    semaphore_signal(sem);
    return NULL;
}

int main(){
    pthread_t thr1,thr2,thr3;
    semaphore sem;
    semaphore_init(&sem,1);
    pthread_create(&thr1,NULL,thrFunc,(void*)&sem);
    pthread_create(&thr2,NULL,thrFunc,(void*)&sem);
    pthread_create(&thr3,NULL,thrFunc,(void*)&sem);
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    pthread_join(thr3,NULL);
    cout<<"global variable after thread execution : "<<g_variable<<"\n";
}
