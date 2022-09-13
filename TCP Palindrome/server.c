#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	char str[100],str2[100];
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
				
		if(i==1){
			comm_fd = accept(listen_fd,(struct sockaddr*)NULL,NULL);	
		}
		i++;
		bzero(str,100);
		bzero(str2,100);
		
		recv(comm_fd,str,100,0);
		printf("Message received - %s",str);

		strcpy(str2, str);
		//bzero(str2,strlen(str2));
		// char temp;
		// for(int j=0,i=strlen(str)-1; i>=0 && j<strlen(str); i--,j++){
		// 	str2[j] = str[i];
		// }
		int flag=0;
		for(int i=0; i<(strlen(str)-1)/2; i++){
			if(str2[strlen(str2)-2-i]!=str[i]){
				strcpy(sendline, "NO! It is not a palindrome.");
				flag=1;
				break;
			}
		}
		if(flag==0){
			strcpy(sendline, "YES! It is a palindrome.");
		}
		// str2[strlen(str2)]='\0';
		// printf("%s\n",str);
		// printf("%s\n",str2);
		// printf("%d %d\n",(int)strlen(str),(int)strlen(str2));
		// if (printf("%d\n",strncmp(str, str2, strlen(str))) == 0) strcpy(sendline, "YES! It is a palindrome.");
		// else strcpy(sendline, "NO! It is not a palindrome.");
		// //fgets(sendline,100,stdin);
		printf("%s\n",sendline);
		send(comm_fd,sendline,strlen(sendline),0);
		
		
	}
	close(comm_fd);
	
	
}