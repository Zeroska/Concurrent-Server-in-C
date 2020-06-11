#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>

//Server using thread based or process based

#define PORT 80
#define BUFSIZE 1024
#define BACK_LOG 10
#define SOCKET int //SOCKET is integer
#define ISVALIDSOCKET(s) ((s) => 0)

//I would define a bunch of code for later usage

enum CODE{
  EXIT_PROGRAM,
  SOMETHING
};

//Should you create a function to small pieces

void initUNIX(SOCKET socketfd, struct sockaddr_in server){
  printf("Server is starting\n");
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *bind_address;
  getaddrinfo(0, "80", &hints, &bind_address);

  if( (socketfd = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol)) < 0){
    fprintf(stderr,"Something went wrong in the socket() in initiUNIX()\n");
    exit(EXIT_FAILURE);
  }

  if ((bind(socketfd, bind_address->ai_addr, bind_address->ai_addrlen)) < 0){
    fprintf(stderr, "Something went wrong in the bind() in initUNIX()\n");
    exit(EXIT_FAILURE);
  }
  freeaddrinfo(bind_address);

  if (listen(socketfd,BACK_LOG)){
    fprintf(stderr, "Something went wrong in the listen() in initUNIX()\n");
    exit(EXIT_FAILURE);
  }
  
  //now we accept all the shit
}

void init(int socketfd, struct addrinfo hints){
  printf("Seting up socket\n");
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  struct addrinfo * bind_addr;
  getaddrinfo(0,"80", &hints, &bind_addr);
  //we could code like the style of the Hand-on book, but the thing
}

void handle_connection(int socket, struct sockaddr_in server, fd_set socketSet){
  //loop until receive exit code
  socklen_t serverLen = sizeof server;
  while(!EXIT_PROGRAM){
    fprintf(stdout,"[*] Init Finished!\n");
    accept(socket,(struct sockaddr*) &server, &serverLen);
    //should create another process to handle connection right here
  }
}

void thread_pool(){

}



int main(void){
  int socket_listen,socket2,socket3;
  char buffer[BUFSIZE];
  struct addrinfo hints;
  struct sockaddr_in serverAddr;

  struct timeval timeout;
  timeout.tv_sec = 1; //hold the value of second 
  timeout.tv_usec = 500000; //hold the value of microsecond

  fd_set socketSet;
  
  //zero the set and then set socket to the socket set
  FD_ZERO(&socketSet);
  FD_SET(socket_listen, &socketSet);
  FD_SET(socket2,&socketSet);
  FD_SET(socket3,&socketSet);
  SOCKET max_socket;

  fd_set copy;
  max_socket = socket_listen;
  if(socket2 > max_socket) max_socket = socket2;
  if(socket3 > max_socket) max_socket = socket3;
  copy = socketSet;
  select(max_socket + 1, &copy, 0, 0, &timeout);

  //This hold section [IS KINDA MISUNDERSTOOD]
  socklen_t len = sizeof serverAddr;
  if(FD_ISSET(socket_listen, &copy)){
    accept(socket_listen, (struct sockaddr*)&serverAddr, &len);
  }

  if(FD_ISSET(socket2, &copy)){
    recv(socket2, buffer, BUFSIZE,0);
  }

  if(FD_ISSET(socket3, &copy)){
    recv(socket3, buffer, BUFSIZE, 0);
  }

  //This would initial all the property for the Server 
  initUNIX(socket_listen, serverAddr);

  //Handle connection

  return 0;
}
