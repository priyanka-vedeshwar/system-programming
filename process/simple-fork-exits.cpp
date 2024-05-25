/*
        exit and _exit calls from child to demonstare calling of exit handlers.
*/
#include<iostream>
#include<unistd.h>  

using namespace std;
int p = 1;

void exitHandler(){
    p = 2;
    cout<<"Exit handler of parent\n";
}
void exitHandlerChild(){
    p = 3;
    cout<<"Exit handler of child\n";
}

int main(){
    int pid;
    int status;
    int pdes[2];
    //register exit Handler of parent
    atexit(exitHandler);
    
    if(pipe(pdes) < 0){
        perror("Pipe");
        exit(EXIT_FAILURE);
    } 
    cout<<"In parent, before fork\n";
    cout<<"Value of p : "<<p<<"\n";
    
    pid = fork();
    
    if(pid < 0){
        cout<<"Error creating child process\n";
        exit(0);
    }
    if(pid == 0){
        //In child process
        //register exit handler at child
        atexit(exitHandlerChild);
        cout<<"In child, exiting now\n";
        //_exit(EXIT_SUCCESS);
        exit(EXIT_SUCCESS);
        cout<<"Shouldn't reach this point\n";
    }else{
        wait(&status);
        cout<<"In Parent after exit from child\n";
        cout<<"Value of p : "<<p<<"\n";
        exit(EXIT_SUCCESS);
    }
}