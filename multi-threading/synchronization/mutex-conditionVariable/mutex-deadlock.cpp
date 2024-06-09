/*
    A deadlock can occur when two or more blocked threads are waiting for each 
    other to release a resource such as a mutex.
    Program demonstrates a simple deadlock that occurs due to each thread waiting 
    to acquire a second mutex which in turn can be succesful only when the first 
    acquired mutex is released.
*/

#include <iostream>
#include <unistd.h>
#include <thread>

using namespace std;

mutex m1;
mutex m2;

void thrFunc1(){
    cout<<"Acquiring mutex m1 by thread 1\n";
    m1.lock();
    sleep(2);
    cout<<"Acquiring mutex m2 by thread 1\n";
    m2.lock();
}

void thrFunc2(){
    cout<<"Acquiring mutex m2 by thread 2\n";
    m2.lock();
    sleep(2);
    cout<<"Acquiring mutex m1 by thread 2\n";
    m1.lock();
}

int main(){
    thread t1(thrFunc1);
    thread t2(thrFunc2);
    t1.join();
    t2.join();
}
