/*
    Demonstration of exit analysis macros that inform 
    why a process exited. 
    WIFEXITED : process terminated normally with exit or _exit.
    WIFSIGNALED : process terminated because it received a signal.
    WIFSTOPPED : process is stopped. 
    WIFCONTINUED : process received SIGCONT.
*/
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

// Define a macro for a specific child exit code (if we do not
// specify this exit code during compilation with the 
// -D CHILD_EXIT_CODE=[number] option), by default, it will be 42:
#ifndef CHILD_EXIT_CODE
#define CHILD_EXIT_CODE 42
#endif

void exitCheck(int);
void child_routine(int);
void parent_routine(pid_t *,int);

int	main(void)
{
	pid_t	pid[3]; 
    for(int i = 0;i < 3 ;i++){
        pid[i] = fork();
        if(pid[i] < 0){
            perror("Fork");
            exit(EXIT_FAILURE);
        }else if (pid[i] == 0){
            //In child
            child_routine(i);
        }else{
            //In parent
            parent_routine(pid,i);
        }    
        usleep(1000);
    }
	
}

// Child process routine:
void child_routine(int index)
{
    switch(index){
        case 0 :
                cout<<"Child with pid "<< getpid() <<": Exiting with exit code : "<<CHILD_EXIT_CODE<<"\n";
	            exit(CHILD_EXIT_CODE);
        case 1 :
                cout<<"Child with pid "<< getpid() <<": Waiting till killed...\n";
                while(1);
        case 2:
                cout<<"Child with pid "<< getpid() <<": Waiting to receive CONTINUE signal...\n";
                while(1);
    }	
}

// Parent process routine:
void parent_routine(pid_t *pid,int index)
{
	int	status;
	cout<<"Parent: I'm the parent.\n";
	cout<<"Parent: Waiting for my child with PID "<<pid[index]<<"\n";
	switch (index)
    {
    case 0 :
        waitpid(pid[index],&status,0);
        exitCheck(status);    
        break;
    case 1 :
        usleep(1000);
        kill(pid[index], SIGKILL);
        waitpid(pid[index], &status, 0);
        exitCheck(status);
        break;
    case 2 :
        usleep(1000);
        //kill(pid[index],SIGSTOP);
        kill(pid[index],SIGCONT);
        waitpid(pid[index],&status,WCONTINUED);
        exitCheck(status);
    }
}

void exitCheck(int status){
    if(WIFEXITED(status))
        cout<<"Parent : Child exited normally with exit code : "<<WEXITSTATUS(status)<<"\n\n";
    else if(WIFSIGNALED(status))
        cout<<"Parent : Child exited via signal with exit code : "<<WTERMSIG(status)<<"\n\n";
    else if(WIFSTOPPED(status))
        cout<<"Parent : Child stopped via signal with exit code : "<<WSTOPSIG(status)<<"\n\n";
    else if(WIFCONTINUED(status))
        cout<<"Parent : Child received SIGCONT \n";
}