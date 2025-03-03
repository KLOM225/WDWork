#include <my_header.h>

/* Usage: ./02_read filename */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);    

    char buf[1024] = {0};
    ssize_t sret = read(fd, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    printf("readcount = %ld, buf =  %s\n",sret, buf); 
    
    close(fd);
    return 0;
}

