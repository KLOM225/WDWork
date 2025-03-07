#include <my_header.h>


int main(void){

    char *ip = "192.168.140.128";
    char *port = "8080";

    struct sockaddr_in socketAddr;
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(atoi(port));
    socketAddr.sin_addr.s_addr = inet_addr(ip);

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket");

    int retconn = connect(socket_fd,(struct sockaddr *)&socketAddr, sizeof(struct sockaddr));
    ERROR_CHECK(retconn, -1, "connect");

    char buff[10] = {0};
    int retread = read(STDIN_FILENO, buff, sizeof(buff));
    ERROR_CHECK(retread, -1, "read");
    printf("buff %s\n",buff);
    
    if(strlen(buff) == 2 && buff[0] == '1'){
        char *http = "1";
        int httplen = strlen(http);

        int retsend = send(socket_fd, &httplen, sizeof(int), 0);
        ERROR_CHECK(retsend, -1, "send");
        send(socket_fd, http, httplen, 0);
    }

    if(strlen(buff) == 2 && buff[0] == '2'){
        char *http = "2";
        int httplen = strlen(http);

        send(socket_fd, &httplen, sizeof(int), 0);
        send(socket_fd, http, httplen, 0);
    }

    // char buf_name[100];
    //  int name_len = 0;

    //  recv(socket_fd, &name_len, sizeof(int), MSG_WAITALL);
    //  recv(socket_fd, buf_name, name_len, MSG_WAITALL);

    char ret[1024];
    ssize_t retlen = 0;

    recv(socket_fd, &retlen, sizeof(ssize_t), MSG_WAITALL);
    recv(socket_fd, ret, retlen, MSG_WAITALL);
    printf("------\n");
    printf("%s\n",ret);
    printf("------\n");

    close(socket_fd);
    return 0;
}

