#include <my_header.h>

/* Usage: ./06_dirnet2 pathname */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);
    //打开目录流并检查错误
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");

    struct dirent *pdirent;
    //循环打印目录信息
    while((pdirent = readdir(dirp)) != NULL){
        printf("inode num = %lu, reclen = %hu, type = %u, name = %s, off = %lu \n",
               pdirent->d_ino, pdirent->d_reclen,
               pdirent->d_type,pdirent->d_name,
               pdirent->d_off 
               );
    }
    
    //关闭目录流
    closedir(dirp);
    return 0;
}

