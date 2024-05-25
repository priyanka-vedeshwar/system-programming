/*
    Program to demostrate piping of three process 
    Example, terminal command in form of string | greap ea | sort
    //refernce : https://www.rozmichelle.com/pipes-forks-dups/
*/

#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    int pdes_1[2];
    int pid_1;
    if (pipe(pdes_1) < 0 ){
        perror("Pipe");
        exit(EXIT_FAILURE);
    }
    pid_1 = fork();
    if(pid_1 < 0){
        perror("Fork_1");
        exit(EXIT_FAILURE);
    }else if (pid_1 == 0){
            //child process
            dup2(pdes_1[0],0); //connect read of pipe1 to the std input of child#1 
            close(pdes_1[0]);
            close(pdes_1[1]);
            int pdes_2[2];
            int pid_2;
            //create second pipe
            if (pipe(pdes_2) < 0 ){
                std::cout<<"Error creating pipe";
                return 0;
            }
            pid_2 = fork();
            //fork another child process at child#1
            if(pid_2 < 0){
                perror("Fork_2");
                exit(EXIT_FAILURE);
            }else if(pid_2 == 0){
                //child of child [say child#2]
                dup2(pdes_2[0],0); //connect read end of pipe2 to std input of child#2
                close(pdes_2[0]);
                close(pdes_2[1]);
                execl("/bin/sh","sh","-c","sort",NULL);
            }else{
                //child#1
                dup2(pdes_2[1],1); //connect write end of pipe2 to std output of child#1
                close(pdes_2[0]); 
                execl("/bin/sh","sh","-c","grep ea",NULL);
                close(pdes_2[1]); //close write end of pipe#2 to indicate end of input from child#1
            }
    }else{
        //parent process
        close(pdes_1[0]);
        char *words[]={"Zeal","Bear","Ate","Love"};
        for (auto str : words){
            dprintf(pdes_1[1],"%s\n",str); //write data to pipe#1 from parent process
        }
        close(pdes_1[1]); //close write end of pipe#1 to indicate end of input from parent process
        wait(NULL);
    }

   return 0;
}
