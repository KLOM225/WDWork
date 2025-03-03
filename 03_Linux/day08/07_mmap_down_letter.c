#include <my_header.h>

/*User: ./07_mmap_down_letter filename */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1], O_RDWR, 0666);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);  
    
    struct stat rb;
    int size = fstat(fd,&rb);
    ERROR_CHECK(size, -1, "fstat");
    size = rb.st_size;
    
    char *p =(char *) mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    for(int i = 0; i < size; i++){
        p[i] = tolower(p[i]); 
    }

    printf("%s\n",p);

    munmap(p, 5);
    close(fd);
    return 0;
}

