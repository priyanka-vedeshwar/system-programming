/*
    pthread implementation of mutex and condition variable.    
*/

#include <iostream>
#include <pthread.h>

using namespace std;

struct account{
    pthread_mutex_t m;
    pthread_cond_t cv;
    long balance;
    long amount;
};


void account_init(struct account *account){
    if (pthread_mutex_init(&(account->m),0))
        exit(EXIT_FAILURE);
    if(pthread_cond_init(&(account->cv),0))
        exit(EXIT_FAILURE);
    account->balance = 0;
    account->amount = 0;
    return;
}

void *deposit_money(void *arg){
    struct account *account = (struct account *)arg;
    pthread_mutex_lock(&(account->m));
    account->balance += account->amount;
    cout<<"Amount "<<account->amount<<" added to account, Banlace is : "<<account->balance<<"\n";
    pthread_mutex_unlock(&(account->m));
    pthread_cond_broadcast(&(account->cv));
    return NULL;
}

void *withdraw_money(void *arg){
    struct account *account = (struct account *)arg;
    pthread_mutex_lock(&(account->m));
    while(account->balance ==0 ){
        pthread_cond_wait(&(account->cv),&(account->m));
    }
    if(account->balance >= account->amount){
        account->balance -= account->amount;
        cout<<"Amount "<<account->amount<<" deducted from account, Balance is : "<<account->balance<<"\n";
    }else{
        cout<<"Not enough fund to withdraw the entered amount\n";
    }
    cout<<"Current Balance is : "<<account->balance<<"\n";
    return NULL;
}

int main(){
    struct account *acc;
    account_init(acc);
    pthread_t t1,t2;
    acc->amount =500;
    pthread_create(&t1,NULL,withdraw_money,(void*)acc);
    pthread_create(&t2,NULL,deposit_money,(void*)acc);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}