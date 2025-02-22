#include <my_header.h>

/* Usage: ./01_openfile filename*/
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);
    
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    
    printf("fd : %d\n",fd);
    
    close(fd);
    return 0;
}

