#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    int sock_fd;
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);

    char buffer[100];
    int n = 0;

    int len = sizeof(servaddr);

    for ( ; ; )
    {
        bzero(buffer, 100);
        n = 0;
        printf("\nTo server: ");
        while ((buffer[n++] = getchar()) != '\n');
        sendto(sock_fd, buffer, 100, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

        bzero(buffer, 100);
        recvfrom(sock_fd, buffer, 100, 0, (struct sockaddr*)&servaddr, &len);
        printf("From server: %s", buffer);
    }
    
    
    return 0;
}