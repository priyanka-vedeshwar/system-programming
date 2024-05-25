/*
    popen implementation that shall execute the command passed to it 
    while creating a pipe between the calling program and the executed command.
    Two modes r : that can be used to read output of command execution 
    and mode w : that can used to pass on inputs to command from parent
    are available.
*/

#include<iostream>
#include<unistd.h>

using namespace std;

FILE *
popen(const char* command, const char * mode){
    FILE *fdes;
    int pid;
    int pdes[2];
    if(*mode != 'r' && *mode !='w'){
        cout<<"Wrong mode, should either be r or w\n";
        return NULL;
    }
    if(pipe(pdes) < 0){
        perror("Pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    
    if(pid < 0 ){
        perror("Fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //In child
        if( *mode == 'r'){
            int tpdes = pdes[1];
            close(pdes[0]);
            dup2(tpdes,STDOUT_FILENO);
            close(tpdes);
        }else if(*mode == 'w'){
            close(pdes[1]);
			if (pdes[0] != STDIN_FILENO) {
				dup2(pdes[0], STDIN_FILENO);
				close(pdes[0]);
            }
        }
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(0);
        }else{
            if(*mode == 'r'){
                fdes = fdopen(pdes[0], mode);
		        close(pdes[1]);
            }else{
                fdes = fdopen(pdes[1], mode);
		        close(pdes[0]);
            }
            wait(NULL);
            return fdes;
        }
};
