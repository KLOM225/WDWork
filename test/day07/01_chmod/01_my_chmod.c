#include <my_header.h>

/* Usage: ./01_chmod pathname mode  */
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);
    mode_t mode;
    sscanf(argv[2], "%o", &mode);

    int ret = chmod(argv[1], mode);
    ERROR_CHECK(ret, -1, "chmod");
    return 0;
}

