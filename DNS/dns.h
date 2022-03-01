typedef struct{
    char domain[30];
    char ip[30];
}TABLE;

typedef struct{
    int found;
    char ip[30];
    int redirect_ip;
}RESPONSE;