/* 
   A program demonstrating channel creation between two threads
   Mutex is used to lock the critical section i.e. Buffer and 
   Conditional variables read and write are used to notify writing 
   and reading of data in buffer respectively.
*/

#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<vector>

using namespace std;
class channel{
    vector<string> buffer;
    mutex mtx;
    condition_variable read_condition;
    condition_variable write_condition;
    bool data_available = false;

    public:
        void write(string data){
            unique_lock<mutex> lock(mtx);
            write_condition.wait(lock, [&]() { return !data_available; });
            buffer.push_back(data);
            data_available = true;
            read_condition.notify_all();
        }

        string read(){
              unique_lock<mutex> lock(mtx);
              read_condition.wait(lock, [&]() {return data_available;});
              string temp = buffer[buffer.size()-1];
              buffer.pop_back(); 
              data_available = false;
              write_condition.notify_all();
              return temp;
        }
};

int main(){
     channel channel1;
    auto writeFunc = [&](){
        for(int i =0;i<8;i++)
            channel1.write("Hello there");
    };
    auto readFunc = [&](){
        for(int i =0 ; i<8;i++)
            cout<<"read Func :  "<<channel1.read()<<"\n";
    };
    thread th1(writeFunc), th2(readFunc);
    th1.join();
    th2.join();
    return 0;
}