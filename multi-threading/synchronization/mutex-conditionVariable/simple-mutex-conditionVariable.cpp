/*
    While mutex is a synchronization primitive that grants exclusive access of the shared 
    resource to just one thread, multi threaded applications also require signalling mechanism
    to synchronise with other thread's execution.
    Condition variables allow threads to block on conditions witout polling/utilizing CPU cycles.
    A thread gets blocked when it's waiting on a condition. Upon fulfillment of condition in 
    another thread, with notify method associated with condition variable, threads waiting on 
    it are woken up and scheduled for execution.    
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
condition_variable cv;
long balance = 0;

void deposit_money(int amount){
    lock_guard<mutex> lg(m);
    balance += amount;
    cout<<"Amount "<<amount<<" added to account, Banlace is : "<<balance<<"\n";
    cv.notify_one();
}

void withdraw_money(int amount){
    unique_lock<mutex> ul(m);
    cv.wait(ul, []{return (balance!=0) ? true : false; });
    if(balance >= amount){
        balance -= amount;
        cout<<"Amount "<<amount<<" deducted from account, Balance is : "<<balance<<"\n";
    }else{
        cout<<"Not enough fund to withdraw the entered amount\n";
    }
    cout<<"Current Balance is : "<<balance<<"\n";
}

int main(){
    thread t1(withdraw_money,500);
    this_thread::sleep_for(chrono::seconds(2));
    thread t2(deposit_money,500);
    t1.join();
    t2.join();

}