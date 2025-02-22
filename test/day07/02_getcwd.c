#include <my_header.h>

/* Usage: ./02_getcwd */
int main(void){
    // 用栈数组作为getcwd的返回值
    
    char path[1024] ={0};
    char *p = getcwd(path, sizeof(path));
    ERROR_CHECK(p, NULL, "getcwd");
    printf("cwd = %s\n ", path);
    return 0;
}

