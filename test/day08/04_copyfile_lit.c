#include <my_header.h>

/* Usage: ./04_copyfile_lit src dst */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open src");
    printf("fdr = %d\n", fdr);    
    
    int fdw = open(argv[2],O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(fdw, -1, "open dst");
    printf("fdw = %d\n", fdw);    
    
    char buf[1024] = {0};
    ssize_t wsize = read(fdr, buf, sizeof(buf));
    write(fdw, buf, wsize);
    
    close(fdr);
    close(fdw);
    return 0;
}

