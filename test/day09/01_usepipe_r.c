#include <my_header.h>

int main(void){
    //开启管道读端
    int pipe_r = open("1.pipe", O_RDONLY);
    ERROR_CHECK(pipe_r, -1, "open pipe write");
    printf("fd = %d\n", pipe_r);    
    //读取数据
    while(1){
        char buf[60] = {0};
        ssize_t ret = read(pipe_r, buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "pipe_r");
        printf("buf : %s\n",buf);
    }
    close(pipe_r);
    return 0;
}

