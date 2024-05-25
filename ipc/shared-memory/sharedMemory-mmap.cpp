/*
    Anonymous memory mapping to be shared between processes
    i.e memory allocated without a file / persistant storage 
    associated with it.
*/
#include<iostream>
#include<unistd.h>
#include<sys/mman.h>
using namespace std;

int main(){
    void *shared_mem = NULL;
    int pid;
    //Creating a shared memory
    shared_mem = mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //In child
        //attaching to shared memory
        char msg[] = "Hello from child\n";
        memcpy(shared_mem,msg,sizeof(msg));
        _exit(0);
    }else{
        wait(NULL);
        char msg[30];
        memcpy(msg,shared_mem,sizeof(msg));
        cout<<"Message written by child : "<<msg;
    }
}