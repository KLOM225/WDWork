#include <my_header.h>

#define BLOCK_SIZE (8*1024*8)

/*User: ./08_mmap_copyfile src dest */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    
    int src_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open");
    printf("src = %d\n", src_fd);  
    
    int dest_fd = open(argv[2], O_RDWR | O_CREAT |O_TRUNC, 0666);
    ERROR_CHECK(dest_fd, -1, "open");
    printf("dest = %d\n", dest_fd);  

    off_t src_size = lseek(src_fd, 0, SEEK_END);
    
    //struct stat rb;
    //int size = fstat(src_fd, &rb);
    //ERROR_CHECK(size, -1, "fstat");
    //off_t src_size = rb.st_size;
    
    int ret = ftruncate(dest_fd, src_size);
    ERROR_CHECK(ret, -1, "ftruncate");
    
    off_t offest = 0;
    
    while(offest < src_size){
    off_t curr_size = ((offest +BLOCK_SIZE) > src_size) ? (src_size - offest) : BLOCK_SIZE;

    void *src_p = mmap(NULL, curr_size, PROT_READ , MAP_SHARED, src_fd, offest);
    ERROR_CHECK(src_p, MAP_FAILED, "src mmap");

    void *dest_p = mmap(NULL, curr_size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_fd, offest);
    ERROR_CHECK(dest_p, MAP_FAILED, "dest mmap");

    memcpy(dest_p, src_p, curr_size);
    
    munmap(src_p, curr_size);
    munmap(dest_p, curr_size);
    
    offest += curr_size;
    }


    close(src_fd);
    close(dest_fd);
    return 0;
}

