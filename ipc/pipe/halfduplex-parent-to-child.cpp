/*
    Pipes are unidirectional communication channels that allow
    one process to pass data to another and chain commands together. 
    Half duplex pipe communication from parent to child is demonstrated here.

*/
#include<iostream>
#include<unistd.h>

using namespace std;
char input(){
    return getchar();
}

int main(){

    int pdes[2];
    int pid;
    if (pipe(pdes) < 0 ){
        perror("Pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if(pid < 0){
        perror("Fork");
        exit(EXIT_FAILURE);
    }if (pid == 0){
        //child process
        dup2(pdes[0],STDIN_FILENO); //connect read end of pipe to std input of child process
        close(pdes[0]); 
        close(pdes[1]);
        system("cat"); //exec family of functions don't work for all commands
        //execl("/bin/sh","sh","-c","top",NULL);    
        }else{
        //parent process
        char in;
        close(pdes[0]); 
        cout<<"Enter filename to be viewed\n";
        do{
            in = getchar();
            write(pdes[1],&in,sizeof(in));
        }while (in != '\n');
        close(pdes[1]); //close write end of pipe to signify end of input from parent process
        wait(NULL);
        cout<<"Exiting parent process\n";
    }
}
