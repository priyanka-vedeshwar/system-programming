/*
    A signal is a notification message used in Unix and POSIX-compliant operating systems.
    Kernel maintains a two bit vector tables for each process : pending signal and blocked signal table.
    When a process resumes, pending unblocked pending signal set and actions are taken for the respective signal.
    A signal can be raised by kernel, process or hardware.
    This program demonstrates signal raised by parent process to child via kill command.
*/
#include <iostream>
#include <signal.h>
#include <unistd.h>

//if -D SIGNAL not provided while compiling,
//default signal is set to SIGKILL
#ifndef SIGNAL
#define SIGNAL 9
#endif

void child_routine();
void parent_routine(int,int);
void checkExit(int);

using namespace std;

int main(int argc, char *argv[]){
    pid_t pid;
    if(argc != 2){
        cout<<"Enter signal number to be sent from parent to child\n";
        exit(EXIT_FAILURE);
    }    
    pid = fork();
    int signal = stoi(argv[1]);
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //In child process
        child_routine();
    }else{
        //In parent process
        parent_routine(pid,signal);
    }
}

void child_routine(){
    while(1)
        cout<<"Waiting to receive a signal\n";
}
void parent_routine(int pid,int signal){
    int status;
    kill(pid,signal);
    waitpid(pid,&status,0);
    checkExit(status);
}

void checkExit(int status){
    if(WIFSIGNALED(status))
        cout<<"Child exited due to signal "<<WTERMSIG(status)<<"\n";
}