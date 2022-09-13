#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

int main(){
	int listen_fd,comm_fd,num1,num2,ans;
	char rec1[10],rec2[10],send1[10];
	struct sockaddr_in serveraddr,cli;
	int sizecli = sizeof(cli);
	
	listen_fd = socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&serveraddr,sizeof(serveraddr));
	bzero(&cli,sizeof(cli));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(22000);
	
	bind(listen_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	
	int i=0;
	while(1){
		//listen(listen_fd,10);
		bzero(rec1,10);
		bzero(rec2,10);
		bzero(send1,10);
		
		//if(i==0){
		//	comm_fd = accept(listen_fd,(struct sockaddr*)NULL,NULL);
		//}
		//i++;
		
		int i=recvfrom(listen_fd,rec1,10,MSG_WAITALL,(struct sockaddr*)&cli,&sizecli);
		//int j=recv(comm_fd,rec2,10,0);
		printf("%d\n",i);
		
		//printf("Number recieved are : \n%s\n ",rec1);
		
		char *number1 = strtok(rec1,"\n");
		char *number2 = strtok(NULL,"\n");
		printf("Numbers are : %s,%s\n",number1,number2);
		
		num1 = atoi(number1);
		num2 = atoi(number2);
		
		ans = num1+num2;
		
		sprintf(send1,"%d",ans);
		
		sendto(listen_fd,send1,strlen(send1),0,(struct sockaddr*)&cli,sizeof(cli));
		printf("Message sent\n");
		
	}
}