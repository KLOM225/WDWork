#include <my_header.h>

/*User: ./08_mmap_copyfile src dest */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    int src_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open");
    printf("src = %d\n", src_fd);  
    
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(dest_fd, -1, "open");
    printf("dest = %d\n", dest_fd);  
    
    struct stat rb;
    int size = fstat(src_fd, &rb);
    ERROR_CHECK(size, -1, "fstat");
    size = rb.st_size;
    
    while(1){
    char *p =(char *) mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, src_fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    }


    munmap(p, 5);
    close(src_fd);
    close(dest_fd);
    return 0;
}

