#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	char str[100];
	int listen_fd,comm_fd;
	struct sockaddr_in servaddr;  
	
	
	listen_fd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(22000);

	bind(listen_fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	
	int i=1;
	while(1){
		char sendline[100];
		listen(listen_fd,10);
        if(((strncmp(str,"exit",4))==0) || i==1){
			comm_fd = accept(listen_fd,(struct sockaddr*)NULL,NULL);
			i=1;	
		}
		i++;
		bzero(str,100);
		
		recv(comm_fd,str,100,0);
		printf("Message received - %s",str);

		fgets(sendline,100,stdin);
		
		send(comm_fd,sendline,strlen(sendline),0);
		
		
	}
	close(comm_fd);
}