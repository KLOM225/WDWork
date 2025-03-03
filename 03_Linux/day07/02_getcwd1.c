#include <my_header.h>

/* Usage: ./02_getcwd1 */
int main(void){                                  
    char* cwd = getcwd(NULL, 0);
    ERROR_CHECK(cwd, NULL, "getcwd");

    puts(cwd);
    free(cwd);
    return 0;
}

