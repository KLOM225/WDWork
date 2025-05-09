#include <my_header.hpp>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using std::cout;

int flag = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *start_routine1(void *arg){
    while(1){
    pthread_mutex_lock(&mutex);
    while(1 == flag ){//将if换成while，是为了防止发生异常唤醒的情况
        pthread_cond_wait(&cond, &mutex);
        
    }
    if(flag == 0){
        cout << "A" << endl;
        flag = 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    }
    if(flag == 2){
        cout << "C" << endl;
        flag = 0;
        break;
    }
    }
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    //return NULL;
    pthread_exit(NULL);//退出子线程
    
}

void *start_routine2(void *arg){

    pthread_mutex_lock(&mutex);
    while(0 == flag){//将if换成while，是为了防止发生异常唤醒的情况
        pthread_cond_wait(&cond, &mutex);
    }
        
    cout << "B" << endl;
    flag = 2;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    //return NULL;
    pthread_exit(NULL);//退出子线程
    
}

//void *start_routine3(void *arg){
//
//    pthread_mutex_lock(&mutex);
//    while(2 != flag){//将if换成while，是为了防止发生异常唤醒的情况
//        pthread_cond_wait(&cond, &mutex);
//    }
//        
//    cout << "C" << endl;
//    flag = 0;
//    pthread_mutex_unlock(&mutex);
//    pthread_cond_signal(&cond);
//    //return NULL;
//    pthread_exit(NULL);//退出子线程
//    
//}
int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, NULL, start_routine1, NULL);
    pthread_create(&pthid2, NULL, start_routine2, NULL);
    //pthread_create(&pthid3, NULL, start_routine3, NULL);
     
    cout << "pthread main id  : " << pthread_self() << endl;    

    pthread_join(pthid1, nullptr);
    pthread_join(pthid2, nullptr);
    //pthread_join(pthid3, nullptr);
    
    pthread_mutex_destroy(&mutex); 
    pthread_cond_destroy(&cond);
    return 0;
}

