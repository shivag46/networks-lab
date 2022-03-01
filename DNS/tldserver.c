#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include"dns.h"

int main(int argc, char **argv)
{
    int serversocket, n = 0, cnt=2;
    int redirect = 7230;
    char req[100];
    TABLE table[100];
    struct sockaddr_in servaddr, cliaddr;

    //Filling table
    strcpy(table[0].domain, "ssn.edu");
    strcpy(table[0].ip, "50.123.45.6");
    strcpy(table[1].domain, "boaz.com");
    strcpy(table[1].ip, "32.23.123.34");

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(serversocket < 0)
        perror("Cannot create socket!\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(7229);

    if(bind(serversocket,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0 ){
        perror("Bind error:");
    }

    while(1){
        int len = sizeof(cliaddr);
        printf("\nWaiting for requests...\n");
        recvfrom(serversocket,req,sizeof(req),MSG_WAITALL,(struct sockaddr*)&cliaddr,&len);

        printf("Connection accepted from %s:%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

        int found = 0,i=0;
        for(;i<cnt;i++){
            if(strcmp(req,table[i].domain) == 0){
                found = 1;
                break;
            }
        }

        RESPONSE response;
        if(found){
            response.found = 1;
            strcpy(response.ip, table[i].ip);
            printf("\n\nRequested domain:%s, found: %d, IP:%s\nSending response...",req,response.found,response.ip);
        }
        else{
            response.found = 0;
            response.redirect_ip = redirect;
            printf("\n\nRequested domain:%s, found: %d, Redirect IP:%d\nSending response...",req,response.found,response.redirect_ip);
        }
        sendto(serversocket,&response,sizeof(response),MSG_WAITALL,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    }
}