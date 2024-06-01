/*
    Simple chatbot using message queue.
*/
#include <iostream>
#include <unistd.h>
#include <sys/msg.h>
#include <signal.h>

void set_signal_action();
void signal_handler(int);

using namespace std;

struct message_buf{
    long mtype;
    char data[100];
};

int main(){
    //set_signal_action();
    pid_t pid;
    struct message_buf msg_in, msg_out;
    char buf[20];
    int msgid = msgget(12,IPC_CREAT|0666);
    if(fork() == 0){
        // In child
        // Receive data from process one
        while(1){
            msgrcv(msgid,&msg_in,sizeof(msg_in),1,0);
            cout<<"Message from process 1 :"<<msg_in.data<<"\n";
            cout<<"Process 2 : Enter data\n";
            fflush(stdout); 
        }
    }else{
        // In parent
        // Send data to process one
        while(1){
            msg_out.mtype = 2;
            cout<<"Process 2 : Enter data\n";
            cin>>buf;
            strcpy(msg_out.data,buf);
            msgsnd(msgid,&msg_out,sizeof(msg_out),0);
        }   
    }
    msgctl(msgid,IPC_RMID,NULL);    

}
void set_signal_action(){
    struct sigaction sa;
    bzero(&sa,sizeof(sa));
    sa.sa_handler = &signal_handler;
    sigaction(SIGINT,&sa,NULL);
}

void signal_handler(int SIGNAL){
    if(SIGNAL == SIGINT)
        cout<<"Intercepted SIGINT. Press Ctrl \\ to exit \n";
}