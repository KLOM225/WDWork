#include <my_header.h>

int main(){ 
    
    key_t key = ftok("./01_pipea", 10);
    printf("%d\n",key);
    int shmid = shmget(key, 4096, 0600 | IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");
    printf("%d\n",shmid);
    char *p = (char *)shmat(shmid, NULL, 0);
    strcpy(p, "How are you");
    
    return 0;
}

