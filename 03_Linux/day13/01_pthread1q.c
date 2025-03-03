#include <my_header.h>

int global_num = 0;

void *pthread_main(void *p){
    for(int i = 0; i < 1000000; i++){
        global_num++;
    }
    return NULL;
}

int main(void){
    //创建三个线程 
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_create(&thread1, NULL, pthread_main, NULL); 
    pthread_create(&thread2, NULL, pthread_main, NULL); 
    pthread_create(&thread3, NULL, pthread_main, NULL); 
    //先阻塞5秒，让三个线程运行完
    sleep(5);

    printf("global_num = %d\n", global_num);
    return 0;
}

