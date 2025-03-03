#include <my_header.h>


int main(void){
    
    //char *add = "www.baidu.com";
    char *add = "www.jd.com";
    
    struct addrinfo *ret;
    
    getaddrinfo(add, NULL, NULL, &ret);
    
    for(struct addrinfo *p = ret; p !=NULL; p = p->ai_next){
        
        if(p->ai_family == AF_INET){
            struct sockaddr_in *sockaddrIPv4 = (struct sockaddr_in *)p->ai_addr; 
            struct in_addr Ipv4 = sockaddrIPv4->sin_addr;
            char *Ip = inet_ntoa(Ipv4);
            printf("IPv4 IP = %s\n",Ip);
        }

    }
    freeaddrinfo(ret);
    return 0;
}

