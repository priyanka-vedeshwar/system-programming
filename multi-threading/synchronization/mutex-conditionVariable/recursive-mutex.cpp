/*
    Recursive mutex are mutex that can be locked multiple times, recursively
    without causing deadlocks. 
     
    They are used in recursive functions using mutex or when one function 
    calls another function that tries to acquire same mutex.
    If recursive mutex are not used in such scenarios, a deadlock can occur 
    as the called function will wait endlessly for the callee function to 
    release the same mutex it is waiting to acquire.
*/

#include <iostream>
#include <mutex>
#include <thread>
 
using namespace std;

class r_mutex
{
   recursive_mutex m;
   // mutex m; //will result in deadlock if regular mutex is used.
   string shared;
public:
    void fun1()
    {
        lock_guard<recursive_mutex> lk(m);
        shared = "Function 1";
        cout << "In function 1, shared variable is now " << shared << '\n';
    }
    void fun2()
    {
        lock_guard<recursive_mutex> lk(m);
        shared = "Function 2";
        cout << "In function 2, shared variable is now " << shared << '\n';
        fun1(); // recursive lock becomes useful here
        cout << "Back in function 2, shared variable is " << shared << '\n';
    }
};
 
int main() 
{
    r_mutex rMut;
    thread t1(&r_mutex::fun1, &rMut);
    thread t2(&r_mutex::fun2, &rMut);
    t1.join();
    t2.join();
}