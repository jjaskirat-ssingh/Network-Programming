#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;

    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);

    if (bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Binding error");
    }

    char buffer[100];
    int n = 100;
    char send1[20];
    int len = sizeof(cliaddr);

    for ( ; ; )
    {
        bzero(buffer, 100);
        recvfrom(sock_fd, buffer, 100, 0, (struct sockaddr*)&cliaddr, &len);
        printf("From client: %s", buffer);

        //bzero(buffer, 100);
        n = 0;
        // printf("To client: ");
        // while ((buffer[n++] = getchar()) != '\n');
        sprintf(send1,"%d",(int)strlen(buffer)-1);
        sendto(sock_fd, send1, 100, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }

    close(sock_fd);

    return 0;
}