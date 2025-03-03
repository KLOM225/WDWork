#include <my_header.h>

/* Usage: ./04_copyfile_big src dst */
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open src");
    printf("fdr = %d\n", fdr);    

    int fdw = open(argv[2],O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(fdw, -1, "open dst");
    printf("fdw = %d\n", fdw);    

    char buf[1024] = {0};
    ssize_t sret;
    while((sret = read(fdr, buf, sizeof(buf)))>0){
        write(fdw, buf, sret);
    }
    // while(1){
    //     memset(buf,0,sizeof(buf));
    //     ssize_t sret = read(fdr, buf, sizeof(buf)); 
    //     if(sret == 0){
    //         break;
    //     }
    //     write(fdw, buf, sret);
    // }
    close(fdr);
    close(fdw);
    return 0;
}

