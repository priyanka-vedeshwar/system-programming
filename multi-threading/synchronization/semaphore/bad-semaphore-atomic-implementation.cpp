/*
    Semaphore is a synchronization primitive that enables synchronisation in multi-threaded 
    programming by signaling of events.
    Operation on semaphore is atomic but the there is still a busy wait which wastes 
    CPU cycles that some other process/thread might be able to use productively. 
*/

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <queue>

using namespace std;

struct Semaphore
{
    Semaphore():sem(1)
    {}
    void wait()
    {
       auto oldValue = sem.load();
       while (oldValue == 0 || !sem.compare_exchange_strong(oldValue, oldValue - 1))
           oldValue = sem.load();
        sem.fetch_sub(1);
    }
    void signal()
    {
        sem.fetch_add(1);
    }

    private :
    std::atomic<int> sem ;

};

Semaphore s; 
int g_variable =  0;

void *thrFunc(void *){
    s.wait(); 
    cout<<"Entering critical section\n";
    g_variable++;
    sleep(3);
    cout<<"Exiting critical section\n";
    s.signal();
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