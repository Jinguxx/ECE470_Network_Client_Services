//
//  TCP_client.h
//  ECE470Project1
//
//  Created by Jing Ma on 3/2/21.
//

#ifndef TCP_client_h
#define TCP_client_h

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
#define BACKLOG 5
#define DE_SERVER_PORT 12345
#define DE_CLIENT_PORT 12345
#define MAXBUFFERLEN 1024
#define SERV_IP "127.0.0.1"
using namespace std;

class client
{
private:
    int sockfd_server;
    int connection;
    int sockfd_client;
    int sockfd_client_acc;
    string server_route;
    string client_route;
    int server_port;
    int client_port;
    sockaddr_in server_address={0};
    sockaddr_in client_address={0};
public:
    client();
    client(string serverIP,int serverPort);
    int send_message(string message);
    string receive_message();
    void closing_all();
    void close_single(int option);
};

client::client()
{
    connection=1;
    sockfd_client_acc=0;
    server_route=SERV_IP;
    sockfd_server=socket(AF_INET,SOCK_STREAM,0);
    sockfd_client=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd_server==-1)
    {
    perror("Failed to create socket for Communicating with the server");
    exit(EXIT_FAILURE);
    }

    if(sockfd_client==-1)
    {
    perror("Failed to create socket for listening for message from Server");
    exit(EXIT_FAILURE);
    }
    //To send messages
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(DE_SERVER_PORT);
    inet_pton(AF_INET,server_route.c_str(),&(server_address.sin_addr));
    memset(&(server_address.sin_zero),'\0',8);

    //To make the client listen but especially to bind it to a port
    client_address.sin_family=AF_INET;
    client_address.sin_port=ntohs(DE_CLIENT_PORT);
    client_address.sin_addr.s_addr=INADDR_ANY;
    memset(&(client_address.sin_zero),'\0',8);

}

client::client(string serverIP,int port)
{
    connection=1;
    sockfd_client_acc=0;
    server_route=serverIP;
    sockfd_server=socket(AF_INET,SOCK_STREAM,0);
    sockfd_client=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd_server==-1)
    {
    perror("Failed to create socket for Communicating with the server");
    exit(EXIT_FAILURE);
    }

    if(sockfd_client==-1)
    {
    perror("Failed to create socket for listening for message from Server");
    exit(EXIT_FAILURE);
    }
    //To send messages
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);
    inet_pton(AF_INET,server_route.c_str(),&(server_address.sin_addr));
    memset(&(server_address.sin_zero),'\0',8);

    //To make the client listen but especially to bind it to a port
    client_address.sin_family=AF_INET;
    client_address.sin_port=ntohs(port);
    client_address.sin_addr.s_addr=INADDR_ANY;
    memset(&(client_address.sin_zero),'\0',8);
}




int client::send_message(string message)
{
    char buffer[MAXBUFFERLEN];
    FILE *stream;
    //Converting string to char[]
    int tn=message.size();
    char temp[tn+1];
    strcpy(temp,message.c_str());
    //Creating the stream for our message
    stream=fmemopen(temp,strlen(temp),"r");
    int num_char_read=fread(buffer+1,sizeof(char),sizeof(buffer),stream);
    buffer[0]=num_char_read;
    sockfd_server=socket(AF_INET,SOCK_STREAM,0);
    connection=connect(sockfd_server,(const struct sockaddr*)&server_address,sizeof(struct sockaddr));
    if(connection==-1)
    {
    perror("Failure to connect to server");
    exit(EXIT_FAILURE);
    close(sockfd_server);
    return -1;
    }
    int sending=write(sockfd_server,(const char*)buffer,strlen(buffer)+1);
    if(sending==-1)
    {
    perror("Failure to send package");
    exit(EXIT_FAILURE);
    close(sockfd_server);
    return -1;
    }
    close(sockfd_server);
    return 1;
}

string client::receive_message()
{
    FILE *stream;
    char *bp;
    size_t size;
    stream=open_memstream(&bp,&size);
    char buffer[MAXBUFFERLEN];
    
    if(sockfd_client_acc==0)
    {
    int rc = bind(sockfd_client,(const struct sockaddr*)&client_address,sizeof(client_address));
    if(rc==-1)
    {
    perror("Failed to bind client_address to socket");
    close(sockfd_client);
    exit(EXIT_FAILURE);
    }
    int listening=listen(sockfd_client,BACKLOG);
    if(listening==-1)
    {
    perror("Failed to listen to socket");
    close(sockfd_client);
    exit(EXIT_FAILURE);
    }
    }

    unsigned int sin_size=sizeof(struct sockaddr_in);
    sockfd_client_acc=accept(sockfd_client,(struct sockaddr *)&server_address,&sin_size);
    int received=read(sockfd_client_acc,(char *)buffer,MAXBUFFERLEN);
    if(received==-1)
    {
    perror("Failed to received package");
    close(sockfd_client);
    close(sockfd_client_acc);
    exit(EXIT_FAILURE);
    }
    fwrite(buffer+1,sizeof(char),buffer[0],stream);
    fflush(stream);
    string temp(bp);
    return temp;
}

void client::closing_all()
{
    close(sockfd_server);
    close(sockfd_client);
    close(sockfd_client_acc);
}

void client::close_single(int option)
{
    if(option==0)
    {
        close(sockfd_server);
    }
    else if(option==2)
    {
        close(sockfd_client);
    }
    else if(option==3)
    {
        close(sockfd_client_acc);
    }
    else
    {
        close(sockfd_server);
        close(sockfd_client);
        close(sockfd_client_acc);
    }
    
}

#endif /* TCP_client_h */
