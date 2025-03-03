#include <my_header.h>

int main(){
    int pipefd[2];
    pipe(pipefd);

    if(fork() == 0){
        close(pipefd[1]);
        char buf[10] = {0};
        read(pipefd[0], buf, sizeof(buf));
        printf("son buf%s\n",buf);


    }else{
        close(pipefd[0]);
       // char buf[10] = {0};
        
        write(pipefd[1], "hello a", 7);
        wait(NULL);
    
    }

    return 0;
}

