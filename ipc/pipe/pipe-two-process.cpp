/*
    Program to demostrate piping of two process 
    Example, terminal command in form of string | grep 
    //refernce : https://www.rozmichelle.com/pipes-forks-dups/
*/

#include <iostream>
#include <unistd.h>

using namespace std;

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
    }else if (pid == 0){
        //child process
        dup2(pdes[0],STDIN_FILENO); //connect read end to std input of child process
        close(pdes[0]); 
        close(pdes[1]);
        //To grep "ea" from the string provided.
        execl("/bin/sh","sh","-c","grep ea",NULL);
    }else{
        //parent process
        close(pdes[0]); 
        char *words[]={"Zeal","Bear","Ate","Love"};
        for (auto str : words){
            dprintf(pdes[1],"%s\n",str); //write to pipe
        }
        close(pdes[1]); //close write end of pipe to signify end of input from parent process
        wait(NULL);
    }
   exit(EXIT_SUCCESS);
}
