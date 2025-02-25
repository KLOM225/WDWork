#include <my_header.h>

int main(){

    if(fork() == 0){
        execl("./work3_b", "./work3_b", (char *)0);

    }else{
        wait(NULL);
    }
    
    return 0;
}

