#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(){
	char str[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(22000);
	
	bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	int i = 1;
	while(1){
	
		listen(listen_fd, 10);
		if(i == 1){
			comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
		}
		i++;
		
		bzero(str, 100);
		recv(comm_fd, str, 100, 0);
		printf("Echoing back - %s", str);
		send(comm_fd, str, strlen(str), 0);
	}
	close(comm_fd);	

}
