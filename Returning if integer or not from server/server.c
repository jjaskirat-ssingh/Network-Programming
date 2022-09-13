#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(){
    int listen_fd,comm_fd;
    float num;
    char send1[10],rec[10];
    struct sockaddr_in serveraddr;
    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(22000);
    bind(listen_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    int i=0; 
    while(1){
        bzero(send1,10);
        bzero(rec,10);
        int flag=0;
        listen(listen_fd,10);
        if(i==0){
        comm_fd = accept(listen_fd,(struct sockaddr*)NULL,NULL);
        }
        i++;
        recv(comm_fd,rec,10,0);
        printf("Number recieved is %s\n",rec);
        for(int i=strlen(rec)-1; rec[i]!='.'; i--){
            if(rec[i]!='0'){
                flag=1;
                break;
            }
        }
        
        if(flag==1){
            send(comm_fd,"real",strlen("real"),0);
        }
        else {
            send(comm_fd,"integer",strlen("integer"),0);
        }
    }
        close(listen_fd);
}