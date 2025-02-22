#include <my_header.h>

/* Usage:  ./03_chdir pathname */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 2);

    //先打印当前路径
    char buf[1024] = {0};
    char *ret1 = getcwd(buf, sizeof(buf));
    ERROR_CHECK(ret1, NULL, "getcwd");
    printf("改变之前的路径：");
    puts(buf);

    //改变路径
    int ret2 = chdir(argv[1]);
    ERROR_CHECK(ret2, -1, "chdir");

    //打印改变后的路径
    char *ret3 = getcwd(buf, sizeof(buf));
    ERROR_CHECK(ret3, NULL, "getcwd");
    printf("改变之后的路径：");
    puts(buf);
    
    return 0;
}

