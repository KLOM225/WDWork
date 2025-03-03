#include <my_header.h>

/* Usage:  */
int main(){
    int fd_r = open("1.pipe",O_RDONLY);
    ERROR_CHECK(fd_r, -1, "open pipe w");
    int fd_w = open("2.pipe",O_WRONLY);
    ERROR_CHECK(fd_w, -1, "open pipe r");

    fd_set set;

    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(fd_r, &set);

        select(10, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            if(buf[0] == '1' && strlen(buf) == 2){
                break;
            }
            write(fd_w, buf, sizeof(buf));
        } else if (FD_ISSET(fd_r, &set)){
            char buf[60] = {0};
            ssize_t ret = read(STDIN_FILENO, buf, sizeof(buf));
            if(ret == 0){
                break;
            }

        }

    }
    close(fd_r);
    close(fd_w);
    return 0;
}

