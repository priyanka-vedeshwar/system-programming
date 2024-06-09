/*
    A signal is a notification message used in Unix and POSIX-compliant operating systems.
    Each signal has a default action associated with it which can be either to terminate 
    the process (with or without core dump), ignore the signal or suspend the process till SIGCONT.
    Apart from these default actions, signals can be intercepted at the process and their behaviour can be modified.
    Exception being SIGKILL and SIGSTOP signals whose default action of termination can't be changed.
    
    Program experiments with signal handler being inherited by child process;
    setting different signal handlers in child and parent and observing the 
    behaviour by killing child and parent seperately, in different order.  
*/
#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

void set_signal_common();
void set_signal_action(int);
void signal_handler_child(int);
void signal_handler_parent(int);
void signal_handler_common(int);

int main(){
  //set_signal_common(); //test inheritence of signal handler by child
    if(fork()){
        //In child
        set_signal_action(1); //signal_handler for child;
        cout<<"Child pid "<<getpid()<<"\n";
        while(1);
    }else{
        //In parent
        set_signal_action(0); //signal_handler for parent;
        cout<<"Parent pid "<<getpid()<<"\n";
        while(1);
    }
    return 0;
}

void set_signal_common(){
    struct sigaction sa;
    bzero(&sa,sizeof(sa));
    sa.sa_handler = &signal_handler_common;
    sigaction(SIGINT,&sa,NULL);

}
void signal_handler_common(int SIGNAL){
    if(SIGNAL == SIGINT)
        cout<<"Intercepted SIGINT.\n";
    exit(0);
}
void set_signal_action(int child){
    struct sigaction sa;
    bzero(&sa,sizeof(sa));
    if(child){
    sa.sa_handler = &signal_handler_child;
    }else{
        sa.sa_handler = &signal_handler_parent;
    }
    sigaction(SIGINT,&sa,NULL);
}

void signal_handler_child(int SIGNAL){
    if(SIGNAL == SIGINT){
        cout<<"Intercepted SIGINT in child.\n";
        cout<<"Exiting out of child now\n";
        exit(EXIT_SUCCESS);
    }    

}
void signal_handler_parent(int SIGNAL){
    if(SIGNAL == SIGINT){
        cout<<"Intercepted SIGINT in parent.\n";
        cout<<"Exiting out of parent now\n";
        exit(EXIT_SUCCESS);
    }
}