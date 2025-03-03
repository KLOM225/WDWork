#include <my_header.h>


int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1], O_RDWR, 0666);
    ERROR_CHECK(fd, -1, "open");

    printf("fd = %d\n", fd);  

    int ret = ftruncate(fd, 5);
    ERROR_CHECK(ret, -1, "ftruncate");

    char *p =(char *) mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    for(int i = 0; i < 5; i++){
        printf("%c", p[i]);
    }
    printf("\n");

    p[4] = 'r';

    for(int i = 0; i < 5; i++){
        printf("%c", p[i]);
    }
    printf("\n");

    munmap(p, 5);
    close(fd);
    return 0;
}

