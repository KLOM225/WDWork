#include <my_header.h>

/* Usage: ./03_write filename */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");
        
    ssize_t sret = write(fd, "hello",5);
    printf("sret = %ld\n", sret);
    close(fd);
    return 0;
}

