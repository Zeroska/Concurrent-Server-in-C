#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h> //this is for the signal handling 
#include <time.h>

//#include <netinet/in.h>

#define PORT 1337
#define BACK_LOG 9
#define MAX_BUF 536

void handle_connection(int sockfd, char sendBuffer[], char recvBuffer[]){
    send(sockfd, sendBuffer, MAX_BUF,0);
    printf("Message sent: %s\n", sendBuffer);
    recv(sockfd, recvBuffer, MAX_BUF, 0);
    printf("Message recieve: %s\n", recvBuffer);
}

//calc for the format 
double calc(char recvBuffer[]){
    
}

//void function can return to indicate the function is terminated for the readabilty
void sig_chld(int signo){
    pid_t pid;
    int stat;
    while((pid =waitpid(-1,&stat, WNOHANG))> 0){
        printf("Child %d terminated\n", pid);
    }
    return;
}

int main(void){
    int connfd, listenfd;
    struct sigaction something;
    char sendBuffer[MAX_BUF] = "Hello Client";
    char recvBuffer[MAX_BUF] = {0};
    pid_t pid;
    void sig_child(int);
    struct sockaddr_in serverAddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&serverAddr,0 , sizeof serverAddr);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&serverAddr, sizeof serverAddr);
    listen(listenfd, BACK_LOG);
    socklen_t len = sizeof serverAddr;
    signal(SIGCHLD, sig_chld);
    while(1){
        //I think because this is in the for loop this would actually
        //fine
        connfd = accept(listenfd, (struct sockaddr *)&serverAddr, &len);

        if ((pid = fork()) == 0){ //Child process
            close(listenfd);
            printf("Process %d\n", pid);
            handle_connection(connfd, sendBuffer,recvBuffer);
            close(connfd);
            exit(EXIT_SUCCESS); //to terminate the child process 
        }
        //this happen concurrent 
        //but this thing gonna do first
        printf("Server is doing nothing\n");
        //why the fuck they call that on top of the server not in the while loop
        close(connfd);

        //wait(NULL);

    } 
}