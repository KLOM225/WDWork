#include <my_header.h>

/* Usage:  */
int main(){
    //已知文件名称和内容
    char *file_name = "1.txt";
    char *str = "hello";
    //设置自定义协议（火车头协议）
    //协议开头设置将要传输的文件名称大小给对面
    int file_name_len = strlen(file_name);
    int str_len = strlen(str);
    //打开管道写端
    int pipe_wr = open("1.pipe", O_WRONLY);
    //写入协议
    //文件名大小，文件名
    write(pipe_wr, &file_name_len, sizeof(int));
    write(pipe_wr, file_name, file_name_len);
    //内容大小，内容
    write(pipe_wr, &str_len, sizeof(int));
    write(pipe_wr, str, str_len);
    //关闭管道
    close(pipe_wr);
    return 0;
}

