#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int byte_stream[20];
int redbits[10];
int table[10][20];
int encoded_stream[20];
int n = 11,tot = 15,m=4;

void gentable(){
    for(int i=1;i<=m;i++){
        int idx = 1;
        for(int j=1;j<=n;j++){
            if((j & (1<<(i-1))) != 0){
                //printf("%d %d %d \n",i,idx,j & (1<<(i-1)));
                table[i][idx] = j;
                idx++;
            }
        }
    }
}

void encode(){
    int idx = 1;
    for(int i=1;i<=m;i++){
        int cnt = 0;
        int idx = 1;
        for(int j=1;j<=n;j++){
            if(j==table[i][idx]){
                if((byte_stream[j] == 1))
                    cnt++;
                idx++;
            }
        }
        //printf("%d\n",cnt);
        if(cnt%2==0)
            redbits[i] = 0;
        else
            redbits[i] = 1;
    }

    int rcnt = 1, bcnt = 1,p=0;

    for(int i=1;i<=tot;i++){
        if(i == (1<<p)){
            encoded_stream[i] = redbits[rcnt];
            p++;
            rcnt++;
        }
        else{
            encoded_stream[i] = byte_stream[bcnt];
            bcnt++;
        }
    }
}

int main(){
    int given[20] = {0,1,0,1,1,1,1,0,1,1,1,0};
    memcpy(byte_stream,given, sizeof(given));
    gentable();
    encode();

    int server_socket = socket(AF_INET,SOCK_STREAM,0),client_socket;
    struct sockaddr_in serveraddr,cliaddr;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(7228);

    if(bind(server_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
        perror("Bind error:");
    }

    listen(server_socket,10);

    int len = sizeof(cliaddr);
    char a[20];
    for(int i=1;i<=tot;i++){
        char b=(char)(encoded_stream[i]+48);
        strncat(a,&b,1);
    }

    if((client_socket = accept(server_socket,(struct sockaddr*)&cliaddr,&len))>0){
        printf("Accepted from %s:%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    }
    send(client_socket,(const int*)encoded_stream,sizeof(encoded_stream),0);
}