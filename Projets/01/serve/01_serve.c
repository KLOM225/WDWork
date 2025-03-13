#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <pthread.h>
int main() {
int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

char *port = "8000";
char *ip = "0.0.0.0";
struct sockaddr_in sockaddr;
sockaddr.sin_family = AF_INET;
sockaddr.sin_port = htons(atoi(port));
sockaddr.sin_addr.s_addr = inet_addr(ip);
int reuse = 1;
setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
listen(socket_fd, 10);

int net_fd = accept(socket_fd, NULL, NULL);
while(1){
   char buf[60] = {0};
   recv(net_fd, buf, sizeof(buf), 0);
   printf("buf: %s \n", buf);
}

send(net_fd, "hello_zs", 8, MSG_NOSIGNAL);

while(1);

close(socket_fd);
return 0;

}

