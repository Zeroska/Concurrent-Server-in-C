#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#ifdef DEBUG
#endif

#define PORT 1337
#define MAX_BUFF 537



void client_action(int sockfd, char* buffer){

}
void printf_client_information(int sockfd, struct sockaddr_in client){
    
}

//this is the client
int main(int argc, char *argv[])
{
    int sockfd;
    socklen_t len;
    struct sockaddr_in serverAdrr;
    char clientSend[MAX_BUFF];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "error in socket\n");
        exit(EXIT_FAILURE);
    }
    memset(&serverAdrr, 0, sizeof serverAdrr);
    len = sizeof serverAdrr;
    //this is where you can assign IP address
    serverAdrr.sin_family = AF_INET;
    serverAdrr.sin_port = htons(PORT);
    serverAdrr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((connect(sockfd, (struct sockaddr *)&serverAdrr, len)) < 0){
        fprintf(stderr,"error in connect\n");
        exit(EXIT_FAILURE);
    }
    //This is where you send information or something


    return 0;
}