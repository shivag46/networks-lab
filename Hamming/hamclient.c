#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char* argv[]){
    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serveraddr;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(7228);

    connect(server_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    char a[20];
    int b[20];
    recv(server_socket,(int*)b,sizeof(b),0);
    for(int i=1;i<=15;i++)
        printf("%d ",b[i]);
}