#include <my_header.h>

typedef struct {
    int net_fd;
    int alive;
}conn_fd;
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

    //
    conn_fd list[100];
    memset(list, 0, sizeof(list));
    int size = 0;

    // 设置监听集合,用于设置下次监听的内容 
    fd_set next_set;
    FD_ZERO(&next_set);
    FD_SET(sock_fd, &next_set);

    while(1){
        fd_set cur_set;
        memcpy(&cur_set, &next_set, sizeof(next_set));
        select(100, &cur_set, NULL, NULL, NULL);

        if(FD_ISSET(sock_fd, &cur_set)){
            int ret_fd = accept(sock_fd, NULL, NULL);

            list[size].net_fd = ret_fd;
            list[size].alive = 1;
            size++;

            FD_SET(ret_fd, &next_set);
        }

        for(int i = 0; i < size; i++){    
            conn_fd conn = list[i];

            if(conn.alive == 0){
                continue;
            }

            if(FD_ISSET(conn.net_fd, &cur_set)){
                char buf[64] = {0};
                int ret = recv(conn.net_fd, buf, sizeof(buf), 0);

                if(ret == 0){
                    list[i].alive = 0; 
                    FD_CLR(list[i].net_fd, &next_set);

                    close(list[i].net_fd);

                    continue;
                }

                for(int j = 0; j < size; j++){
                    if(list[j].alive == 1 && j != i){
                        send(list[j].net_fd, buf, sizeof(buf), 0);    
                    }
                }
            }
        }   
    }
    close(sock_fd);
    return 0;
}

