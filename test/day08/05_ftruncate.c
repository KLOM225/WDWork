#include <my_header.h>

/* Usage: ./05_ftruncate filename filesize */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    
    printf("fd = %d\n", fd);    
    
    int size;
    sscanf(argv[2]," %d", &size);
    int ret = ftruncate(fd, size);
    ERROR_CHECK(ret, -1, "ftruncate")
    close(fd);
    return 0;
}

