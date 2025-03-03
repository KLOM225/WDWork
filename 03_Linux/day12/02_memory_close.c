#include <my_header.h>

int main(){ 

    key_t key = ftok("./01_pipea", 10);

    int shmid = shmget(key, 4096, IPC_CREAT | 0600);
    ERROR_CHECK(shmid, -1, "shmget");

    char *p = (char *)shmat(shmid, NULL, 0);
    printf("share read: %s\n",p);
    shmdt(p);
    
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

