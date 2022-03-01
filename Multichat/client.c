#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc, char **argv)
{
	size_t len;
	int sockfd, n = 0;
	struct sockaddr_in servaddr;
	char str[1000];
	char buff[1024];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		perror("Cannot create socket!\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(7228);
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	while(1){
		printf("Client:");
		scanf("%s",buff);
		send(sockfd,(const char*)buff,sizeof(buff),0);
		len = sizeof(buff);
		recv(sockfd,(char*)buff,len,0);
		printf("\nServer:%s\n",buff);
	}
	close(sockfd);
	return 0;
}