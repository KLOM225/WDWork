#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <time.h>
#include <sys/wait.h>
#include <dirent.h>
#include <syslog.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>

#define ARGS_CHECK(argc, num){if(argc != num){fprintf(stderr, "args error !\n"); return -1;} }
#define ERROR_CHECK(ret, num, msg){if(ret==num){perror(msg); return -1;}}
#define THREAD_ERROR_CHECK(ret, msg){if(ret!=0){fprintf(stderr, "%s:%s \n", msg,strerror(ret));}}

int main(void){
    //设置IP和端口
    char *port = "9002";
    char *ip = "0.0.0.0";

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
    // 从socket中获取一个连接，创建新的专用链接
    // int connect_fd = accept(sock_fd, NULL, NULL);
    // ERROR_CHECK(connect_fd, -1, "accept");
    // 设置监听集合
    fd_set next_set;
    FD_ZERO(&next_set);
    FD_SET(sock_fd, &next_set);

    int connect_fd;
    while(1){    
        fd_set set;
        memcpy(&set, &next_set, sizeof(next_set));
        select(10, &set, NULL, NULL, NULL);

        if(FD_ISSET(sock_fd, &set)){
            connect_fd = accept(sock_fd, NULL, NULL);
            ERROR_CHECK(connect_fd, -1, "accept");

            printf("fd : %d \n", connect_fd);
            FD_CLR(sock_fd, &next_set);

            FD_SET(STDIN_FILENO, &next_set);
            FD_SET(connect_fd, &next_set);
        }    

        if(FD_ISSET(connect_fd, &set)){
            char buf[64] = {0};
            ssize_t retrecv = recv(connect_fd, buf, sizeof(buf), 0);
            ERROR_CHECK(retrecv, -1, "recv");
            if(retrecv == 0){
                printf("对方断开连接\n");

                FD_CLR(STDIN_FILENO, &next_set);
                FD_CLR(connect_fd, &next_set);
                close(connect_fd);

                FD_SET(sock_fd, &next_set);
                continue;
            }
            printf("------------1------------ \n");
            printf("%s\n", buf);
            printf("------------1------------ \n");
            printf("------------2------------ \n");
            char *str1 = "HTTP/1.1 200 OK\r\n\r\n[\"test1\",\"test2\",\"test3\"]";
            send(connect_fd, str1, strlen(str1), 0);
            printf("%s\n", str1);
            printf("------------2------------ \n");
        }



        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[64] = {0};
            ssize_t r_fd = read(STDIN_FILENO, buf, sizeof(buf)-1);
            ERROR_CHECK(r_fd, -1, "read");

            int retsend = send(connect_fd, buf, sizeof(buf), 0);
            ERROR_CHECK(retsend, -1, "send");

        }
    }
    close(sock_fd);
    close(connect_fd);
    return 0;
}

