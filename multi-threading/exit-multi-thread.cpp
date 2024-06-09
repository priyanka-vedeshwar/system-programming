/*
    Program demonstrating various exits out of threads.
*/
#include <iostream>
#include <unistd.h>

#define PTHREAD

#ifdef THREAD
#include <thread>
#endif
#ifdef PTHREAD
#include <pthread.h>
#endif

using namespace std;

#ifdef THREAD
void thrFunc(){
    cout<<"In thread function\n";
    sleep(2);
    cout<<"Exiting thread\n";
    _exit(0);
}
#endif

#ifdef PTHREAD
    void *thrFunc(void *){
        cout<<"In thread function.\n";
        sleep(2);
        cout<<"Exiting thread.\n";
        //_exit(0); //exit and _exit terminates the entire process
        pthread_exit(0); //terminates only the calling thread
    }
#endif

int main(){
    #ifdef THREAD
    thread t1(thrFunc);
    thread t2(thrFunc);
    thread t3(thrFunc);
    t1.join();
    t2.join();
    t3.join();
    #endif

    #ifdef PTHREAD
    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,thrFunc,NULL);    
    pthread_create(&t2,NULL,thrFunc,NULL);    
    pthread_create(&t3,NULL,thrFunc,NULL);   
    pthread_join(t1,NULL);
    cout<<"returned from t1 \n";
    pthread_join(t2,NULL);
    cout<<"returned from t2 \n";
    pthread_join(t3,NULL); 
    cout<<"returned from t3 \n";
    #endif
}