/*
    When two or more threads need to access a shared resource at the same time, 
    the system needs a synchronization mechanism to ensure that only one thread 
    at a time uses the resource.
    Mutex is a synchronization primitive that grants exclusive access of the shared 
    resource to just one thread.
*/

#include <iostream>
#include <unistd.h>
#include <thread>

using namespace std;
mutex mtx;
int number = 0;

void thrFunc(){
    mtx.lock();
    for(int i = 0;i < 1000000; i++){
        number++;
    }
    mtx.unlock();
}

int main(){
    
    thread t1(thrFunc);
    thread t2(thrFunc);
    t1.join();
    t2.join();
    cout<<"Incremented value after thread executions : "<<number<<"\n";

}