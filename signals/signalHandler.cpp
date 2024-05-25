/*
    A signal is a notification message used in Unix and POSIX-compliant operating systems.
    Each signal has a default action associated with it which can be either to terminate 
    the process (with or without core dump), ignore the signal or suspend the process till SIGCONT.
    Apart from these default actions, signals can be intercepted at the process and their behaviour can be modified.
    Exception being SIGKILL and SIGSTOP signals whose default action of termination can't be changed.
    Program demonstrates a simple signal handler for SIGINT (Ctrl C)/
*/
#include <iostream>
#include <signal.h>

using namespace std;

void set_signal_action();
void signal_handler(int);

int main(){

    set_signal_action();
    while(1);
    return 0;
}

void set_signal_action(){
    struct sigaction sa;
    bzero(&sa,sizeof(sa));
    sa.sa_handler = &signal_handler;
    sigaction(SIGINT,&sa,NULL);
}

void signal_handler(int SIGNAL){
    if(SIGNAL == SIGINT)
        cout<<"Intercepted SIGINT. Press Ctrl \\ to exit \n";
}