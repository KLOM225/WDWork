#include <my_header.h>

/* Usage: ./02_readloop fliename */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);    

    char buf[6] = {0};
    ssize_t readcount;
    while((readcount = read(fd, buf, sizeof(buf)-1))>0){
        printf("readcount = %ld, buf =  %s\n",readcount, buf);
        memset(buf, 0, sizeof(buf));
    }
    ERROR_CHECK(readcount, -1, "read error");
    close(fd);
    return 0;
}

