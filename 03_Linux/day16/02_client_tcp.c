#include <my_header.h>


int main(void){
    //设置IP和端口
    char *port = "8080";
    char *ip = "192.168.140.128";
    
    //设置IPv4sock结构体
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);
    
    //创建socket端点对象
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sock_fd, -1, "socket");

    int retconnect = connect(sock_fd, (struct sockaddr *)&sock, sizeof(sock));
    ERROR_CHECK(retconnect, -1, "connect");
    
    while(1){
    char buf[64] = {0};
    ssize_t r_fd = read(STDIN_FILENO, &buf, sizeof(buf)-1);
    ERROR_CHECK(r_fd, -1, "read");

    ssize_t retsend = send(sock_fd, buf, sizeof(buf), 0);
    ERROR_CHECK(retsend, -1, "send");
    
    memset(buf, 0, sizeof(buf)); 
    int retrecv = recv(sock_fd, buf, sizeof(buf), 0);
    ERROR_CHECK(retrecv, -1, "recv");
    if(retrecv == 0){
        printf("对方断开连接");
        break;
    }
    printf("buf : %s\n",buf);
    }
    

    close(sock_fd);
    return 0;
}

