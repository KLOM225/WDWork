#include <my_header.h>


int main(void){
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(-1, cfd, "socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);
    //127.0.0.1 本地回环地址, 数据不会经过网卡
    //192.168.42.128 本机ip地址
    serveraddr.sin_addr.s_addr = inet_addr("192.168.42.128");

    int ret = connect(cfd,  (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    printf("conn has connected.\n");
    while(1);
    close(cfd);

    return 0;
}

