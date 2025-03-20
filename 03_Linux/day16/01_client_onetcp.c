#include <my_header.h>


int main(void){
    //设置IP和端口
    char *port = "9001:";
    char *ip = "47.97.125.212";
    
    //设置IPv4sock结构体
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    
    //创建socket端点对象
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ERROR_CHECK(sock_fd, -1, "socket");

    int retconnect = connect(sock_fd, (struct sockaddr *)&sock, sizeof(sock));
    ERROR_CHECK(retconnect, -1, "connect");
    
    char buf[64] = {0};
    ssize_t retsend = send(sock_fd, "hello one TCP", 13, 0);
    ERROR_CHECK(retsend, -1, "send");
    
    ssize_t retrecv = recv(sock_fd, buf, sizeof(buf), 0);
    ERROR_CHECK(retrecv, -1, "recv");
    printf("buf : %s\n",buf);

    

    close(sock_fd);
    return 0;
}

