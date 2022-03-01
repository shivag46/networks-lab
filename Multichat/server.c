#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(){
	char buff[1024];
	int server_socket = socket(AF_INET,SOCK_STREAM,0),client_socket;
	struct sockaddr_in server_address,client_address;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(7228);
	server_address.sin_family = AF_INET;

	bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	//listen(server_socket,10);

	while(1){
		int len  = sizeof(client_address),pid;
		//client_socket = accept(server_socket,(struct sockaddr*)&client_address,&len);

		if((pid = fork())==0){
			//printf("Connection accepted from %s:%d\n",inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
			while(1){
				recv(client_socket,(char*)buff,sizeof(buff),0);
				printf("Client:%s\n",buff);
				printf("Server:");
				scanf("%s",buff);
				send(client_socket,(char*)buff,sizeof(buff),0);
			}
		}
	}

	close(client_socket);
} 