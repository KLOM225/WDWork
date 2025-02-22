#include <my_header.h>

/* Usage: ./06_dirnet2 pathname */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);
    //打开目录流并检查错误
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");

    struct dirent *pdirent;
    long loc;
    //循环打印目录信息，并标记file的位置
    while((pdirent = readdir(dirp)) != NULL){
        printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n",
               pdirent->d_ino, pdirent->d_reclen,
               pdirent->d_type,pdirent->d_name);
        if(strcmp("file",pdirent->d_name) == 0){
            loc = telldir(dirp);
        }
    }
    printf("-------------------\n");

    //使目录流指针返回到file的位置
    seekdir(dirp, loc);
    //打印当前文件信息
    pdirent = readdir(dirp);
    printf("inode num = %lu, reclen = %hu, type = %u, name = %s\n",
                 pdirent->d_ino, pdirent->d_reclen,
                 pdirent->d_type,pdirent->d_name);
    
    //关闭目录流
    closedir(dirp);
    return 0;
}

