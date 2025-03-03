#include <my_header.h>

/* Usage: ./06_dirent pathname */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);
    //打开目录流并进行错误处理
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");
    //循环读目录并打印目录信息，结束条件是返回值为NULL
    struct dirent *pdirent;
    while((pdirent = readdir(dirp)) != NULL){
        printf("inode num = %lu  reclen = %hu  type = %u name = %s\n",
               pdirent->d_ino,    
               pdirent->d_reclen,
               pdirent->d_type,
               pdirent->d_name);
    }
    
    //关闭目录流
    closedir(dirp);
    return 0;
}

