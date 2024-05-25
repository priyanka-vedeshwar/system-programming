/*
    Shared memory using shmget
*/
#include<iostream>
#include<unistd.h>
#include<sys/shm.h>
#include<string>

using namespace std;

int main(){
    int pid;
    key_t key = 2345;
    void *shared_memory;
    int shmid;
    //Creating a shared memory
    shmid = shmget(key,1024,0666|IPC_CREAT);
    shared_memory = shmat(shmid,NULL,0);
    cout<<"Shmem attached to parent process at "<<shared_memory<<"\n";
    strcpy((char*)shared_memory,"Hi from parent\n");
    
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //In child
        //attaching to shared memory
        shmid = shmget(key,1024,0666);
        shared_memory = shmat(shmid,NULL,0);
        cout<<"Shmem attached to child process at "<<shared_memory<<"\n";
        cout<<"Data at shmem as read from child is : "<<(char*)shared_memory;
        
        shmdt(shared_memory);
        _exit(0);
    }else{
        wait(NULL);
        //release shared memory
        shmdt(shared_memory);
    }
}