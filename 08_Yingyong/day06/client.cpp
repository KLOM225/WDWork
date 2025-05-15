#include "head.h"

int main()
{
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(-1, cfd, "socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);
    //127.0.0.1 本地回环地址, 数据不会经过网卡
    //192.168.30.129 本机ip地址
    serveraddr.sin_addr.s_addr = inet_addr("192.168.42.128");

    int ret = connect(cfd,  (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    printf("conn has connected.\n");

    fd_set set;

    while(1){
        //在用户态每一次轮询之前都要添加监听
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(cfd, &set);

        //set既是传入参数，也是传出参数
        select(cfd +1, &set, NULL, NULL, NULL);
        //当select函数返回时，set已经被修改了
        //如果是有100个文件描述符就绪，我们是否知道哪些文件描述符发生了事件
        //因此还需要在用户态继续轮询
        if(FD_ISSET(cfd, &set)){
            char buf[60] = {0};
            ssize_t ret = recv(cfd, buf, sizeof(buf), 0);
            if(ret == 0){
                // 可读, 但是读到数据个数0个
                // 说明对方断开链接
                printf("对方断开链接 \n");
                break;
            }
            printf("buf: %s\n", buf);
        }
        if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[60] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            int ret = send(cfd, buf, strlen(buf), 0);
            printf("send %d bytes.\n", ret);
        }
    }

    close(cfd);

    return 0;
}


