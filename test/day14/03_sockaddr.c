#include <my_header.h>


int main(void){
    
    char *port = "9090";
    char *ip = "192.168.3.43";

    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = inet_addr(ip);

    return 0;
}

