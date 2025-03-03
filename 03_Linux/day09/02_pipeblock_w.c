#include <my_header.h>

int main(void){
    //开启管道写端
    int pipe_w = open("1.pipe", O_WRONLY);
    ERROR_CHECK(pipe_w, -1, "open pipe write");
    printf("fd = %d\n", pipe_w);    
   
    //进行写操作
    char buf[4096] = {0};
    int times = 0;
    while(1){
        int ret = write(pipe_w, buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "pipe_w");
        printf("times: %d\n",++times);
    }
    close(pipe_w);
    return 0;
}

