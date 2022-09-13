#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

int main(){
	int listen_fd;
	char num1[10],num2[10],ans[10];
	struct sockaddr_in serveraddr;
	int size = sizeof(serveraddr);
	
	listen_fd = socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&serveraddr,sizeof(serveraddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(22000);
	
	//connect(listen_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	
	while(1){
		bzero(num1,10);
		bzero(num2,10);
		bzero(ans,10);
		
		printf("Enter number1 : ");
		fgets(num1,10,stdin);
		
		printf("Enter number2 : ");
		fgets(num2,10,stdin);
		
		//strcat(num1," ");
		strcat(num1,num2);
		printf("%s\n",num1);
		
		sendto(listen_fd,num1,strlen(num1),0,(struct sockaddr*)&serveraddr,size);
		//send(listen_fd,num2,strlen(num2),0);
		
		printf("Message sent\n");
		
		recvfrom(listen_fd,ans,10,MSG_WAITALL,(struct sockaddr*)&serveraddr,&size);
		
		printf("Answer is %s\n",ans);
	}
	close(listen_fd);
}