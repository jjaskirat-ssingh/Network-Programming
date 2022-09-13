#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(){
    int listen_fd;
    float num;
    char rec[10],send1[10];
    struct sockaddr_in serveraddr;
    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(22000);
    connect(listen_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    while(1){
        bzero(send1,10);
        bzero(rec,10);
        printf("Enter a number : ");
        scanf("%f",&num);
        sprintf(send1,"%f",num);
        send(listen_fd,send1,strlen(send1),0);
        recv(listen_fd,rec,10,0);
        printf("Number is a %s\n",rec);
    }
    close(listen_fd);
}
