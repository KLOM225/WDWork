#include <my_header.h>     


void copy_file(const char *src, const char *dest) {
    FILE *src_fp = fopen(src, "rb");        
    if (src_fp == NULL) {
      
        perror("fopen src");
        exit(1);
    }

    FILE *dest_fp = fopen(dest, "wb");
    if (dest_fp == NULL) {
        perror("fopen dest");
        fclose(src_fp);  
        exit(1);
    }

    
    char buf[1024] = { 0 };
    size_t count;

    
    while ((count = fread(buf, 1, sizeof(buf), src_fp)) > 0) {
        fwrite(buf, 1, count, dest_fp);
    }

   
    fclose(src_fp);
    fclose(dest_fp);
}

int main(int argc, char *argv[]) {
    // ./00_copy_file src dest
    if (argc != 3) {
        fprintf(stderr, "args error!\n");
        exit(1);
    }
    copy_file(argv[1], argv[2]);
    return 0;
}
