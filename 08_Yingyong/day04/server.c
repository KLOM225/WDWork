#include <my_header.h>
#include <iso646.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <errno.h>

#define EPOLL_ARR_SIZE 100
#define EPOLL_TIMEOUT 5000

int main(void){
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(-1, sfd, "socket");
    printf("sfd: %d\n", sfd);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);
    serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    int ret = bind(sfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "bind");

    ret = listen(sfd, 10000);
    ERROR_CHECK(ret, -1, "listen");
    
    //创建epoll的实例
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");
    printf("epfd: %d\n", epfd);
    
    //使用epoll监听sfd的读事件
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = sfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl");

    struct epoll_event arr[EPOLL_ARR_SIZE] = {0};
    while(1){
        int nready = epoll_wait(epfd, arr, EPOLL_ARR_SIZE, -1);
        printf("nready: %d\n", nready);
        if(nready == -1 && errno == EINTR){
            continue;
        }else if(nready == -1){
            perror("epoll_wait");
            return EXIT_FAILURE;
        }else if(nready == 0){
            printf("epoll_timeout. \n");
        }else{
            for(int i = 0; i < nready; ++i){
                int fd = arr[i].data.fd;
                if(fd = sfd){
                    struct sockaddr_in clientaddr;
                    memset(&clientaddr, 0, sizeof(clientaddr));
                    socklen_t len = sizeof(clientaddr);
                    int connfd = accept(sfd, (struct sockaddr *)&clientaddr, &len);
                    ERROR_CHECK(connfd, -1, "accept");
                    
                    event.data.fd = connfd;
                    event.events = EPOLLIN;
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
                    ERROR_CHECK(ret, -1, "epoll_ctl");

                    printf("tcp conn  %s:%d -> %s:%d has connected.\n",
                           inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port),
                           inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
                }
            }
            
        }



    }

    close(epfd);
    close(sfd);
    return 0;
}

