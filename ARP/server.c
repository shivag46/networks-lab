#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct packet{
    char src_ip[30];
    char src_mac[30];
    char dest_ip[30];
    char dest_mac[30];
    char data[30];
}Packet;

int main(int argc, char *argv[])
{
    Packet data_packet;
    printf("Source ip:");
    scanf("%s",data_packet.src_ip);
    printf("Source mac:");
    scanf("%s",data_packet.src_mac);
    printf("Destination ip:");
    scanf("%s",data_packet.dest_ip);
    printf("Data:");
    scanf("%s",data_packet.data);

    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(7228);

    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    listen(server_socket,10);

    int client_socket[10];
    int i= 0;
    struct sockaddr_in client_address[10];
    Packet rcvd_packet;

    while(1){
        socklen_t sz = sizeof(client_address[i]);
        client_socket[i] = accept(server_socket,(struct sockaddr*)&client_address[i],&sz);

        send(client_socket[i],(const void*)&data_packet,sizeof(data_packet),0);

        int recvd = recv(client_socket[i],&rcvd_packet,sizeof(rcvd_packet),0);
        //printf("%d",(int)recvd);

        if(recvd>0){
            printf("Destination MAC received\n");
            printf("%s | %s \n",rcvd_packet.dest_ip,rcvd_packet.dest_mac);
            break;
        }
        i++;
    }

    close(server_socket);
    return 0;
}