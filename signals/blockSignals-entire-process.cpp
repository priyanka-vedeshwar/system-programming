/*
    signal block for SIGINT for the entire process.
*/
#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;


void block_signal(int signal){
    cout<<"Blocking signal "<<signal<<" \n";
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,signal);
    sigprocmask(SIG_BLOCK,&sigset,NULL); 
}

void unblock_signal(int signal){
    cout<<"Unblocking signal \n";
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,signal);
    sigprocmask(SIG_UNBLOCK,&sigset,NULL); 
}

int main(){
    block_signal(SIGINT);
    
    for(int i = 0; i < 5; i++){
        cout<<"Loop.. Ctrl-C will be handled once the signal is unblocked after this loop\n";
        sleep(1);
    }

    unblock_signal(SIGINT);
    //shouldn't reach this point if Ctrl-C was pressed during the loop exec.
    //Upon unblocking, SIGINT due to Ctrl-C sent to the program while it was blocked is taken up.

    //If no Ctrl-C was pressed, check SIGINT action when it's not blocked  
    while(1){
        cout<<"Try Ctrl-C without signal blocked\n";
    }
}
