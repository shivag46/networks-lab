#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc, char **argv){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr;
    servaddr.sin_port = htons(7228);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_family = AF_INET;

    connect(sockfd,(struct sockaddr*)&servaddr, sizeof(servaddr));

    char buff[1024];
    while(1){
        printf("\nClient: ");
        scanf("%s", buff);
        send(sockfd, (char*)buff, sizeof(buff),0);
        recv(sockfd,(char*)buff,sizeof(buff),0);
        printf("Server: %s",buff);
    }

}