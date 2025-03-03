#include <my_header.h>
#
/* Usage: ./07_ls_simple pathname */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);
    //打开目录流并检查错误
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");

    int ret =  chdir(argv[1]);
    ERROR_CHECK(ret, -1, "chdir");

    struct dirent *pdirent;
    while( (pdirent = readdir(dirp)) != NULL){
        struct stat stat_buf;
        int ret2 = stat(pdirent->d_name, &stat_buf);
        ERROR_CHECK(ret2, -1, "stat");

        printf("%o %lu %u %u %lu %lu %s\n",
               stat_buf.st_mode,
               stat_buf.st_nlink,
               stat_buf.st_uid,         
               stat_buf.st_gid,         
               stat_buf.st_size,
               stat_buf.st_mtime,
               pdirent->d_name
              );

    }
    //关闭目录流
    int ret3= closedir(dirp);
    ERROR_CHECK(ret3, -1, "closedir");
    return 0;
}

