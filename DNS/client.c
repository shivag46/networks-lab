#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include"dns.h"

int main(int argc, char **argv)
{
    unsigned int len;
    int serversocket, n = 0;
    struct sockaddr_in servaddr, cliaddr;
    char buff[100];
    RESPONSE response;

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(serversocket < 0)
        perror("Cannot create socket!\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(7228);
    len = sizeof(servaddr);

    printf("Domain name:");
    scanf("%s", buff);
    
    sendto(serversocket, buff, sizeof(buff), MSG_WAITALL, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Request sent to %s:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
    recvfrom(serversocket, &response, sizeof(response), MSG_WAITALL, (struct sockaddr*)&servaddr, &len);
    printf("Received IP:%s",response.ip);
}