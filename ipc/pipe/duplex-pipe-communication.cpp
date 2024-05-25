/*
    Pipes are unidirectional communication channels that allow
    one process to pass data to another and chain commands together. 
    Duplex communication is demonstrated here.As pipes are uni directional, 
    two pipes are used for STDIN and STDOUT data redirection.
*/

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
    pid_t pid;
    int pdes_in[2];
    int pdes_out[2];
    string command;

    if(argc < 2){
        cout<<"Enter command to be passed from parent to child\n";
        exit(EXIT_FAILURE);
    }
    for(int i = 1;i < argc; i++){
        command = command+ argv[i]+ " ";
    }

    if(pipe(pdes_in) < 0){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if(pipe(pdes_out) < 0){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if (pid == 0){
        char c;
        char command[30];
        close(pdes_in[1]);
        close(pdes_out[0]);
        //dup2(pdes_in[0],STDIN_FILENO); //redirecting pdes_in to STDIN doesn't work consistently when paired with execl
        read(pdes_in[0],command,sizeof(command)); //reading data, instead of redirecting to STDIN
        close(pdes_in[0]);
        cout<<"Command received at child is "<<command<<"\n";
        dup2(pdes_out[1],STDOUT_FILENO);
        close(pdes_out[1]);
        execl("/bin/sh","sh","-c",command,NULL);
    }else{
        char buf[1024];
        close(pdes_in[0]);
        close(pdes_out[1]);
        write(pdes_in[1],&command,sizeof(command));
        close(pdes_in[1]);
        wait(NULL);
        read(pdes_out[0],buf,sizeof(buf));
        cout<<"\nSTDOUT of child at parent \n"<<buf<<"\n";
        cout<<"Exiting parent \n";
    }
}