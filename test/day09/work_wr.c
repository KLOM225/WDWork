#include <my_header.h>

/* Usage:  */
int main(){
    //
    char *file_name = "1.txt";
    char *str = "hello";
    
    int file_name_len = strlen(file_name);
    int str_len = strlen(str);

    int pipe_wr = open("1.pipe", O_WRONLY);
    
    write(pipe_wr, &file_name_len, sizeof(int));
    write(pipe_wr, file_name, file_name_len);

    write(pipe_wr, &str_len, sizeof(int));
    write(pipe_wr, str, str_len);
    
    close(pipe_wr);
    return 0;
}

