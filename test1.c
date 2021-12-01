#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

#define PORT 1337
#define MAX_BUF 536 // minimum segment size tcp can transmit

//this is the client
int main(int argc, char* argv[]){
    int sockfd[5];
    char buffer[MAX_BUF] = "Hello boy";
    char recvBuffer[MAX_BUF] = {0};
    struct sockaddr_in serverAddr; // you could use addrinfo
    //this is the error handling
    //but I won't do it
    for(int i = 0; i < 5; ++i){
        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serverAddr, 0, sizeof serverAddr);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        connect(sockfd[i], (struct sockaddr *)&serverAddr, sizeof serverAddr);
        //I should have know which packet is come first
        //
        send(sockfd[i], buffer, MAX_BUF, 0);
        recv(sockfd[i], recvBuffer, MAX_BUF , 0);
        printf("Message from server: %s\n", recvBuffer);
    }  
    
    return 0;
}