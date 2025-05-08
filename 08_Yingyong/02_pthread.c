#include <my_header.h>
#include <pthread.h>

void *start_routine(void *arg){
    printf("sub thread is runing..  \nid: %ld\n", pthread_self());
    while(1);
}

int main(void){
    
    pthread_t pthid;
    pthread_create(&pthid, NULL, start_routine, NULL);

    printf("pthid: %ld\n", pthid);
    
    pthread_t mainid = pthread_self();
    printf("mainid: %ld\n", mainid);
    while(1);
    return 0;
}

