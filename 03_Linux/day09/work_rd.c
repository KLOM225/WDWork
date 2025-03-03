#include <my_header.h>

/* Usage:  */
int main(){
    //
    char file_name[30] = {0};
    char str[1024] = {0};
    
    int file_name_len = 0;
    int str_len = 0;

    int pipe_rd = open("1.pipe", O_RDONLY);
    
    read(pipe_rd, &file_name_len, sizeof(int));
    read(pipe_rd, file_name, file_name_len);
    printf("file_name : %s\n",file_name);

    read(pipe_rd, &str_len, sizeof(int));
    read(pipe_rd, str, str_len);
    printf("str : %s\n",str);
    
    int file_fd = open(file_name, O_RDWR | O_CREAT, 0666);
    write(file_fd, str, str_len);
    
    close(pipe_rd);
    close(file_fd);
    return 0;
}

