#include <my_header.h>
#include <pthread.h>

void *start_routine(void *arg){
    printf("sub thread is runing..  \nid: %ld\n", pthread_self());
    //while(1);
    sleep(3);
    return (void*)1;
}

int main(void){
    
    pthread_t pthid;
    int ret = pthread_create(&pthid, NULL, start_routine, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));
    }
    printf("pthid: %ld\n", pthid);
    
    pthread_t mainid = pthread_self();
    printf("mainid: %ld\n", mainid);
    
    int *p = NULL;
    pthread_join(pthid, (void**)&p);
    printf("p:%d\n", p);

    return 0;
}

