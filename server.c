#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int num;

int main(int argc, char** argv){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr,cliaddr;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7228);
    num = 0;

    bind(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sockfd, 10);
    while(1){
        int len = sizeof(cliaddr);
        int newfd = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
        int pid;
        num++;
        //printf("\nAccepted from ")
        if((pid = fork()) == 0){
            char buff[1024];
            while(1){
                recv(newfd,(char*)buff,sizeof(buff),0);
                printf("\nClient%d: %s",num,buff);
                printf("\nServer: ");
                scanf("%s",buff);
                send(newfd,(char*)buff,sizeof(buff),0);
            }
        }
    }
}