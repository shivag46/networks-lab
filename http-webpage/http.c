#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<errno.h>
#define PORT 80
#define MAX_LIMIT 300
int main(int argc, char* argv[]) {
    if(argc < 2) {
    printf("Usage ./http <Server Name>\n");
    exit(0);
    }

    struct hostent* host;
    struct sockaddr_in address;
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1) {
    printf("Error in Socket Creation...\n");
    close(socket_fd);
    exit(0);
    }
    printf("Socket Created\n");
    char hostname[MAX_LIMIT], hostpath[MAX_LIMIT];
    int i;
    for(i=0; i<strlen(argv[1]); i++) {
        if(argv[1][i] != '/') {
            hostname[i] = argv[1][i];
        }
        else
            break;
    }
    hostname[i] = '\0';
    int j=0;
    for(; i<strlen(argv[1]); i++) {
        hostpath[j] = argv[1][i];
        j++;
    }
    if(j == 0) {
    hostpath[0] = '/';
    j++;
    }
    hostpath[j] = '\0';

    printf("Hostname: %s\n", hostname);
    printf("Hostpath: %s\n", hostpath);
    host = gethostbyname(hostname);
    if(host == NULL) {
    printf("Host can't be reached or doesn't exist\n");
    exit(0);
    }

    char IP[MAX_LIMIT];
    strcpy(IP, inet_ntoa(*((struct in_addr *)host->h_addr_list[0])));
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr(IP);

    if(connect(socket_fd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        printf("Error connecting to server\n");
        printf("errno: %d\n", errno);
        close(socket_fd);
        exit(0);
    }
    printf("Successfully connected to Server\n");
    char request[2046];
    printf("GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",hostpath,hostname);
    sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",hostpath,hostname);
    if(send(socket_fd, request, sizeof(request), 0) < 0) {
        printf("Request can't be sent to server at this moment\n");
        close(socket_fd);
        exit(0);
    }
    char fname[20];
    printf("Enter the filename:");
    scanf(" %[^\n]%*c",fname);
    FILE* fptr = fopen(fname, "w");
    int read_bytes;
    char response[1050];
    bzero(response, sizeof(response));
    while(read_bytes = read(socket_fd, response, sizeof(response)) > 0) {
        fputs(response, fptr);
        bzero(response, sizeof(response));
    }
    printf("\n");
    printf("File downloaded in %s\n", fname);
    fclose(fptr);
    close(socket_fd);
    return 0;
}


//strcpy(ip,inet_ntoa(*((struct in_addr*)host->h_addr_list[0])))