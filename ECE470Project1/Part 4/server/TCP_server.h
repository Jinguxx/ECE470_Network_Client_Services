//
//  TCP_server.h
//  ECE470Project1
//
//  Created by Jing Ma on 3/17/21.
//

#ifndef TCP_server_h
#define TCP_server_h
#include <iostream>
#include <string>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define DEFAULT_PORT 12345
#define BACKLOG 10
#define MAXBUFFERLEN 2048
using namespace std;

class server
{
    private:
        int sockfd;
        int new_fd;
        struct sockaddr_in my_addr;
        struct sockaddr_in their_addr;
        int binding;
        int listening;
        int receiving;
        int sending;
        unsigned int sin_size;
    public:
        server();
        server(int serverPort);
        int initialize_server();
        int send_message(string message);
        string receive_message();
        int closeSockets();
};

//Creating the default constructor
server::server()
{
    //Initiate the socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
    //Configure my address
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons((short)DEFAULT_PORT);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    memset(&(my_addr.sin_zero),'\0',8);
    //Bind the socket
    binding=bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
    if(binding==-1)
    {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }
}

server::server(int serverPort)
{
    //Initiate the socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
    //Configure my address
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons((short)serverPort);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    memset(&(my_addr.sin_zero),'\0',8);
    //Bind the socket
    binding=bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
    if(binding==-1)
    {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
        close(sockfd);
    }
}

int server::initialize_server()
{   
    listening=listen(sockfd,BACKLOG);
    sin_size=sizeof(struct sockaddr_in);
    if(listening==-1)
    {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
        close(sockfd);
        return -1;
    }
    new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size);
    if(new_fd==-1)
    {
        perror("Failed to accept connection");
        exit(EXIT_FAILURE);
        close(sockfd);
        return -1;
    }
    printf("Connected to %s in port %i \n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port));
    return 1;
}

string server::receive_message()
{
    FILE *stream;
    char *bp;
    size_t size;
    char buffer[MAXBUFFERLEN];
    stream=open_memstream(&bp,&size);
    receiving=recv(new_fd,(char*)buffer,MAXBUFFERLEN,0);
    if(receiving==-1)
    {
        perror("Failed to received package");
        exit(EXIT_FAILURE);
        close(sockfd);
        close(new_fd);
    }
    fwrite(buffer+1,sizeof(char),buffer[0],stream);
    fflush(stream);
    string temp(bp);
    return temp;
}


int server::send_message(string message)
{
    char buffer[MAXBUFFERLEN];
    strcpy(buffer,message.c_str());
    int sending=send(new_fd,(const char*)buffer,strlen(buffer)+1,0);
    if(sending==-1)
    {
        perror("Failure to send Package");
        exit(EXIT_FAILURE);
        close(sockfd);
        close(new_fd);
        return -1;
    }
    return 1;
}

int server::closeSockets()
{
    close(sockfd);
    close(new_fd);
    return 1;
}

#endif /* TCP_server_h */
