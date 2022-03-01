#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

typedef struct packet{
    char src_ip[30];
    char src_mac[30];
    char dest_ip[30];
    char dest_mac[30];
    char data[30];
}Packet;

int main(int argc, char*argv[]){
    char ip[30], mac[30];
    printf("IP:");
    scanf("%s",ip);
    printf("MAC:");
    scanf("%s",mac);

    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(7228);

    connect(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    Packet data_packet;
    printf("Connection made. Waiting for ARP request...\n");
    recv(server_socket,&data_packet,sizeof(data_packet),0);

    if(strcmp(ip,data_packet.dest_ip) == 0){
        printf("IP matches\nSending reply...\n");
        strcpy(data_packet.dest_mac,mac);
        send(server_socket,&data_packet,sizeof(data_packet),0);
    }

    else{
        printf("Request received....No match");
        send(server_socket,NULL,NULL,0);
    }
    close(server_socket);
    return 0;
}