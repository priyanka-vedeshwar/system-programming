/*
    A single parent forks multiple children and communicates 
    with them using pipe. 
*/
#include<iostream>
#include<unistd.h>

using namespace std;

int main(){
    int nProcess = 3;
    cout<<"Parent starting child processeses \n";
    for(int i = 0; i < nProcess; i++){
        int pdes[2];
        int pout[2];
        if(pipe(pdes) < 0){
            perror("Pipe");
            exit(EXIT_FAILURE);
        }
        if(pipe(pout) < 0){
            perror("Pipe");
            exit(EXIT_FAILURE);
        }
        if(fork() == 0){
            char buf[3];
            cout<<"In child "<<i<<", pid of child "<<getpid()<<"\n";
            close(pdes[1]);
            close(pout[0]);
            dup2(pout[1],1);
            read(pdes[0],buf,3);
            close(pout[1]);
            close(pdes[0]);
            cout<<"Message from Parent "<<buf<<"\n";
            _exit(0);
        }else{
            char buf[] ="Hi from Parent\n";
            close(pdes[0]);
            write(pdes[1],buf,sizeof(buf));
            close(pdes[1]);
            wait(NULL);
            memset(buf,0,sizeof(buf));
            read(pout[0],buf,30);
            close(pout[0]);
            cout<<"Stdout redirected data from child : "<<buf<<"\n";
            close(pdes[1]);
        }
    }
    cout<<"Parent after all child has ended; pid being "<<getpid()<<"\n";

}