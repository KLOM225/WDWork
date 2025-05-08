#include <my_header.hpp>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using std::cout;

int num = 0;
pthread_mutex_t mutex;

void *start_routine(void *arg){
    int cnt = 100000;
    while(cnt-- > 0)
    {
        pthread_mutex_lock(&mutex);
        num++;
        printf("thread  gnum: %d\n", num);
        pthread_mutex_unlock(&mutex);
    }
    //return NULL;
    pthread_exit(NULL);//退出子线程
    
}

int main(){
    pthread_mutex_init(&mutex, NULL);

    pthread_t pthid1, pthid2, pthid3;
    pthread_create(&pthid1, NULL, start_routine, NULL);
    pthread_create(&pthid2, NULL, start_routine, NULL);
    pthread_create(&pthid3, NULL, start_routine, NULL);
     
    cout << "pthread main id  : " << pthread_self() << endl;    

    pthread_join(pthid1, nullptr);
    pthread_join(pthid2, nullptr);
    pthread_join(pthid3, nullptr);
    
    pthread_mutex_destroy(&mutex);

    printf("num: %d\n", num);
    
    return 0;
}

