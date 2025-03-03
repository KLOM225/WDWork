#include <my_header.h>


int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);    

    char ch;
    while(1){
        ssize_t sret =  read(fd, &ch, 1);
        if(sret == 0){
            break;
        }
        lseek(fd, -1, SEEK_CUR);        
        ch = tolower(ch);
        write(fd, &ch, 1);
    }
    
    close(fd);
    return 0;
}
