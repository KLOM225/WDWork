#include <my_header.h>

/* Usage: ./02_readstdin */
int main(void){
    char buf[1024];
    ssize_t ret = read(0, buf, sizeof(buf));
    ERROR_CHECK(ret, -1, "readstdin");
    printf("ret = %ld , buf = %s\n", ret, buf);

    return 0;
}

