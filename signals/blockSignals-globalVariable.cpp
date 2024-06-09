/*
    Caution needs to be taken when a global variable is manipulated in the signal handler,
    as the signal handler itself can be interrupted by other signals.

    Program demonstrates blocking of SIGQUIT initially, which gets unblocked by SIGINT.
    SIGINT handler itself blocks SIGINT when it updates the value to global variable so 
    that the operation in not interrupted by another SIGINT. 

*/
#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

volatile int g_unblock_sigquit = 0;

void block_signal(int signal){
    cout<<"Blocking signal "<<signal<<" \n";
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,signal);
    sigprocmask(SIG_BLOCK,&sigset,NULL); 
}

void unblock_signal(int signal){
    cout<<"Unblocking signal "<<signal<<"\n";
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,signal);
    sigprocmask(SIG_UNBLOCK,&sigset,NULL); 
}

void sig_handler(int signal){
    if(signal != SIGINT)
        return;
    block_signal(signal);
    g_unblock_sigquit = 1;
    unblock_signal(signal);

}

void signal_set_action(){
    struct sigaction	act;
    bzero(&act, sizeof(act));
    act.sa_handler = &sig_handler;
    sigaction(SIGINT, &act, NULL);
}

int main(){
    signal_set_action();
    block_signal(SIGQUIT); //SIGQUIT via Ctrl-\ is blocked. Unblocking is via SIGINT

    while(1){
        // As interrupt handler for SIGINT changes the global variable, block it while checking
        // global variable's value.
        block_signal(SIGINT); 
        if(g_unblock_sigquit){ //SIGQUIT to be unblocked now.
            unblock_signal(SIGINT);
            unblock_signal(SIGQUIT);
        }else{
            unblock_signal(SIGINT);
        }
        sleep(1);
    }
}
