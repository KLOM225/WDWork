#include <my_header.h>


int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);    

    char ch;
    while(1){
        read(fd, &ch, 1);
        lseek(fd, -1, SEEK_CUR);        
        ch = tolower(ch);
        write(fd, &ch, 1);
    }
    
    close(fd);
    return 0;
}
