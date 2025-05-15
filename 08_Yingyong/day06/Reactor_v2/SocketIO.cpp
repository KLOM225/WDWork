#include "SocketIO.hpp"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>




SocketIO::SocketIO(int fd)
:_fd(fd)
{}

int SocketIO::readn(char * buff, int len){
    int left = len;
    char *p = buff;
    while(left > 0){
        int ret = ::recv(_fd, p, left, 0);
        if(ret == -1 && errno == EINTR){
            continue;
        }else if(ret == -1){
            perror("read");
            return len - left;
        }else if (ret == 0){
            return len - left;
        }else{
            left -= ret;
            p += ret;
        }
    }
    return len -left;
}

int SocketIO::readline(char * buff, int maxlen){
    int left = maxlen -1;
    char *p = buff;
    int ret;
    int total = 0;
    while(left > 0){
        ret = recvPeek(p, left);
        for(int idx = 0; idx != ret; ++idx){
            if(p[idx] == '\n'){
                int sz = idx + 1;
                total += sz;
                p += sz;
                *p = '\0';
                return total;
            }
        }
        
        readn(p, ret);
        left -= ret;
        p += ret;
        total += ret;
    }
    *p = '\0';
    return total;
}
	
int SocketIO::writen(const char * buff, int len){
    int left = len;
    const char *p = buff;
    while(left > 0){
        int ret = ::send(_fd, p, left, 0);
        if(ret == -1 && errno == EINTR){
            continue;
        }else if (ret == -1){
            perror("write");
            return  len -left;
        }else{
            left -= ret;
            p += ret;
        }
    }
    return len - left;
}


int SocketIO::recvPeek(char * buff, int len) const{
    int ret;
    do{
        ret = ::recv(_fd, buff, len, MSG_PEEK);
    } while(ret == -1 && errno == EINTR);
    return ret;
}




