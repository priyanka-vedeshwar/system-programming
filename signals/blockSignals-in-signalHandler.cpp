/*
   A signal is a notification message used in Unix and POSIX-compliant operating systems.
   Signals are asynchronous in nature i.e they can arrive at any point of process execution.
   They can be blocked though i.e signals can be held and delivered till they are unblocked.
   One example of blocking a signal is during a signal handler,
   where the signal handler itself can be interrupted by another signal.
   
   Program to demonstrate blocking of SIGQUIT(Ctrl \) during SIGINT(Ctrl C) handler.
*/
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

volatile int g_signal_unblock = 0;

void set_signal_action();
void signal_handler(int);
void block_signal(int);
void unblock_signal(int);

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

void signal_handler(int signal){
    if(signal != SIGINT)
        return;
    cout<<"In signal handler for SIGINT\n";
    block_signal(SIGQUIT);
    sleep(3); //sleep to let user quit through SIGQUIT(Ctrl \) 
    unblock_signal(SIGINT);
}
void block_signal(int signal){
    cout<<"Blocking SIGQUIT\n";
    sigset_t ss;
    sigemptyset(&ss);
	sigaddset(&ss, signal);
	sigprocmask(SIG_BLOCK, &ss, NULL);
}
void unblock_signal(int signal){
    cout<<"Unblocking SIGQUIT\n";
    sigset_t ss;
    sigemptyset(&ss);
	sigaddset(&ss, signal);
	sigprocmask(SIG_UNBLOCK, &ss, NULL);
}