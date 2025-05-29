#include "head.h"
#include <iostream>
using namespace std;

 typedef struct {
    uint32_t type;   // 消息类型（网络字节序）
    uint32_t length; // 数据长度（网络字节序）
    char value[];    // 变长数据
} TLV;

int main()
{
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(-1, cfd, "socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8100);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.42.128");

    int ret = connect(cfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    printf("conn has connected.\n");

    fd_set set;

    while(1){
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(cfd, &set);

        select(cfd +1, &set, NULL, NULL, NULL);

        if(FD_ISSET(cfd, &set)){
            // 接收缓冲区需要足够大
            char recv_buf[1024] = {0};
            ssize_t ret = recv(cfd, recv_buf, sizeof(recv_buf), 0);
            if(ret == 0){
                printf("对方断开链接 \n");
                break;
            }
            printf("收到 %zd 字节数据\n", ret);

            // 解析接收到的二进制数据
            int recv_type, recv_length;
            memcpy(&recv_type, recv_buf, 4);
            memcpy(&recv_length, recv_buf + 4, 4);
            char recv_str[5] = {0};
            memcpy(recv_str, recv_buf + 8, 5);

            printf("收到数据: type=%d, length=%d, str=%.5s\n", 
                   recv_type, recv_length, recv_str);
        }

         if(FD_ISSET(STDIN_FILENO, &set)){
            char buf[60] = {0};
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf));
            printf("%s\n",buf);
            if(strcmp(buf,"1\n") == 0){
                TLV tlv;
                tlv.type = 2;
                strcpy(tlv.value,"type=1,username=ning");
                tlv.length = strlen(tlv.value);
                printf("%s\n", tlv.value);
                int ret = send(cfd, &tlv, 8 + tlv.length, 0);
                printf("send %d bytes.\n", ret);
            }else if(strcmp(buf,"2\n") == 0){
                TLV tlv;
                tlv.type = 2;
                strcpy(tlv.value,"type=4,username=ning,password=123");
                tlv.length = strlen(tlv.value);
                printf("%s\n", tlv.value);
                int ret = send(cfd, &tlv, 8 + tlv.length, 0);
                printf("send %d bytes.\n", ret);
            }
        }
    }

    close(cfd);
    return 0;
}

