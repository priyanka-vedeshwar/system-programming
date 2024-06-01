/*
    Message queue is a kernel structure that allows processes to exchange information 
    asynchronously.Communication is in the form of passing messages instead of making 
    changes to a shared variable/memeory.
    Here, the program demonstrates a simple message passing 
    from parent to child via message queue according to systemV standards.  
*/

#include <iostream>
#include <unistd.h>
#include <sys/msg.h>

using namespace std;

struct message_buffer{
    long int msgType;
    char message[1024];
}message;

int main(){
    pid_t pid;
    key_t key;
    int msgid;
    char buf[1024];

    key = ftok("msg_q",65);
    msgid = msgget(key,0666 | IPC_CREAT );
    message.msgType = 1;

    pid = fork();
    
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if (pid == 0){
        //In child process
        msgrcv(msgid, &message, sizeof(message), 1, 0); 
        cout<<"Message recived at child via message queue : "<<message.message<<"\n";
    }else{
        //In parent process
        cout<<"Enter data to be pushed to message queue\n";
        cin>>buf;
        cout<<"Data enetered : "<<buf<<"\n";
        memcpy(message.message,buf,sizeof(buf));
        msgsnd(msgid,&message,sizeof(message),0);
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL); 
    }

    




}
