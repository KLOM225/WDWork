#include <my_header.h>

int main(){
    key_t key = ftok("./01_pipea", 1 );
    int shmid = shmget(key, 4096, 0600 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");

    int *p =(int *) shmat(shmid, NULL, 0);
    p[0] = 0;

    if( fork() == 0){
        for(int i = 0; i < 10000000; i++){        
            p[0]++;
        }
    }else{
        for(int i = 0; i < 10000000; i++){        
            p[0]++;
        }
    }
    
    wait(NULL);
    printf("%d \n", p[0]);

    return 0;
}

