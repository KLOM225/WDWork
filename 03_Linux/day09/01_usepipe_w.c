#include <my_header.h>

int main(void){
    //开启管道写端
    int pipe_w = open("1.pipe", O_WRONLY);
    ERROR_CHECK(pipe_w, -1, "open pipe write");
    printf("fd = %d\n", pipe_w);    
    //进行写操作
    while(1){
        int ret = write(pipe_w, "hello", 5);
        ERROR_CHECK(ret, -1, "pipe_w");
        printf("write once \n");
        sleep(5);
    }
    close(pipe_w);
    return 0;
}

