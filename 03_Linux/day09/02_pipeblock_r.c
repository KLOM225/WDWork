#include <my_header.h>

int main(void){
    //开启管道读端
    int pipe_r = open("1.pipe", O_RDONLY);
    ERROR_CHECK(pipe_r, -1, "open pipe write");
    printf("fd = %d\n", pipe_r);    

    //读取数据
    sleep(10);
    char buf[4096] = {0};
    while(1){
        ssize_t ret = read(pipe_r, buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "pipe_r");
        sleep(2);
    }

    close(pipe_r);
    return 0;
}

