#include <my_header.h>
#include <pthread.h>

void *start_routine(void *arg){
    printf("sub thread is runing.. \n");
    while(1);
}

int main(void){
    
    pthread_t pthid;
    pthread_create(&pthid, NULL, start_routine, NULL);

    printf("pthid: %ld\n", pthid);
    
    while(1);
    return 0;
}

