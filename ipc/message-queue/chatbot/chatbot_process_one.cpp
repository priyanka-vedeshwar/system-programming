
/*
    Simple chatbot using message queue.
*/
#include <iostream>
#include <unistd.h>
#include <sys/msg.h>

void set_signal_action();
void signal_handler(int);

using namespace std;

struct message_buf{
    long mtype;
    char data[100];
};

int main(){
    pid_t pid;
    struct message_buf msg_in,msg_out;
    int msgid = msgget(12,IPC_CREAT|0666);    
    char buf[20];
    if(!(fork())){
        // In parent
        // Send data to process two
        while(1){
            msg_out.mtype = 1;
            cout<<"Process 1 : Enter data\n";
            cin>>buf;
            strcpy(msg_out.data,buf);
            msgsnd(msgid,&msg_out,sizeof(msg_out),0);
        }
    }else{
        // In child
        // Receive data from process two
        while(1){
            msgrcv(msgid,&msg_in,sizeof(msg_in),2,0);
            cout<<"Message from process 2 :"<<msg_in.data<<"\n";
            cout<<"Process 1 : Enter data\n";
            fflush(stdout); 
        }
    }
     msgctl(msgid, IPC_RMID, NULL); 
}