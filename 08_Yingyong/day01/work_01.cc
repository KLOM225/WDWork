#include <my_header.hpp>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using std::cout;

void *start_routine(void *arg){
    cout << "pthread id : " << pthread_self() << endl;    
    sleep(2);
    return nullptr;
}

int main(){
    pthread_t pthid1;
    pthread_t pthid2;
    pthread_t pthid3;
    pthread_create(&pthid1, NULL, start_routine, NULL);
    pthread_create(&pthid2, NULL, start_routine, NULL);
    pthread_create(&pthid3, NULL, start_routine, NULL);

     
    cout << "pthread main id  : " << pthread_self() << endl;    

    pthread_join(pthid1, nullptr);
    pthread_join(pthid2, nullptr);
    pthread_join(pthid3, nullptr);

    
    return 0;
}

