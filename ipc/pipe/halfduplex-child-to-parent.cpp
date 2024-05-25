/*
    Pipes are unidirectional communication channels that allow
    one process to pass data to another and chain commands together. 
    Half duplex pipe communication from child to parent is demonstrated here.
*/

#include<iostream>
#include<unistd.h>

using namespace std;

int main(){
    int pid;
    int status;
    int child_to_parent[2];

    if(pipe(child_to_parent) < 0){
        perror("Pipe");
        exit(EXIT_FAILURE);
    } 
    pid = fork();

    if(pid < 0){
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
        //In child process
        close(child_to_parent[0]);
        dup2(child_to_parent[1],1);
        close(child_to_parent[1]);
        execl("/bin/sh","sh","-c","top",NULL);
    }else{
        //In parent process
        char out[2];
        close(child_to_parent[1]);
        char outputChar;
        while (read(child_to_parent[0], &outputChar, sizeof(outputChar)) > 0) 
        {
            cout<<outputChar;
        }
    }
}