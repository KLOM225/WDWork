#include <my_header.h>

int main(){
    if(fork() == 0){
        printf("child session id: %d \n", getsid(0));
        int res = setsid();
        ERROR_CHECK(res, -1, "setsid");
        printf("new session id: %d \n", getsid(0));
        chdir("/");
        while(1){
            sleep(1);
        }
    }else{
        printf("session id: %d \n", getsid(0));
        sleep(10);
    }

    return 0;
}

