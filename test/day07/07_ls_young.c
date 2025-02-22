#include <my_header.h>


void set_type_name(mode_t mode, char *tm_str){
    //设置文件类型
    switch (mode & S_IFMT) {
    case S_IFBLK:   tm_str[0] = 'b';        break;
    case S_IFCHR:   tm_str[0] = 'c';        break;
    case S_IFDIR:   tm_str[0] = 'd';        break;
    case S_IFIFO:   tm_str[0] = 'p';        break;
    case S_IFLNK:   tm_str[0] = 'l';        break;
    case S_IFREG:   tm_str[0] = '-';        break;
    case S_IFSOCK:  tm_str[0] = 's';        break;
    default:        tm_str[0] = '?';        break;
    }
    //设置文件权限
    tm_str[1] = (mode & 0400)? 'x' : '-';
    tm_str[2] = (mode & 0200)? 'x' : '-';
    tm_str[3] = (mode & 0100)? 'x' : '-';

    tm_str[4] = (mode & 0040)? 'x' : '-';
    tm_str[5] = (mode & 0020)? 'x' : '-';
    tm_str[6] = (mode & 0010)? 'x' : '-';

    tm_str[7] = (mode & 0004)? 'x' : '-';
    tm_str[8] = (mode & 0002)? 'x' : '-';
    tm_str[9] = (mode & 0001)? 'x' : '-';
    tm_str[10] = '\0';
}


/* Usage: ./07_ls_young pathname */
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
        
        char mode_name[1024] = {0};
        set_type_name(stat_buf.st_mode, mode_name);
        
        struct passwd *pwuid;
        struct group *grgid;
        pwuid = getpwuid(stat_buf.st_uid);
        grgid = getgrgid(stat_buf.st_gid);

        printf("%s %2lu %s %s %6lu %6lu %s\n",
               mode_name,
               stat_buf.st_nlink,
               pwuid->pw_name,         
               grgid->gr_name,
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

