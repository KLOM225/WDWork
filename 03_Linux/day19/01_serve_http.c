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
    //给socket端点绑定端口和IP
    int retbind = bind(sock_fd, (struct sockaddr *)&sock, sizeof(sock));
    ERROR_CHECK(retbind, -1, "bind");
    // 监听socket端口
    listen(sock_fd, 10);

    int net_fd = accept(sock_fd, NULL, NULL);
    ERROR_CHECK(net_fd, -1, "accept");

    char http[100] = {0};
    int http_len = 0;                                      
    printf("---\n");
    int retrecv = recv(net_fd, &http_len, sizeof(int), MSG_WAITALL);
    ERROR_CHECK(retrecv, -1, "retrecv");
    recv(net_fd, http, http_len, MSG_WAITALL);
    printf("http %s\n",http);

    char file_name[100] = {0};

    if(http[0] == '1'){
        strcpy(file_name, "1.txt");
    }else if(http[0] == '2'){
        strcpy(file_name, "2.txt");
    }
    printf("%s\n",file_name);
    int file_fd = open(file_name, O_RDONLY);
    ERROR_CHECK(file_fd, -1, "open");

    char file_buf[1024] = {0};
    ssize_t readlen =read(file_fd, file_buf, sizeof(file_buf));
    send(net_fd, &readlen, sizeof(ssize_t), 0);
    send(net_fd, file_buf, readlen, 0);
    

    close(sock_fd);
    return 0;
}

