#ifndef _TCP_CLIENT2_H_
#define _TCP_CLIENT2_H_
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
#define MAXBUFFERLEN 4096
#define DEFAULT_IP "127.0.0.1"
using namespace std;

class client
{
    private:
        int sockfd;
        struct sockaddr_in their_addr;
        int connecting;
        int sending;
        int receiving;
    public:
        client();
        client(string serverIP,int serverPort);
        int initialize_client();
        int send_message(string message);
        string receive_message();
        int closeSockets();
};

client::client()
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
    //Configure the server address
    string serverAddress=DEFAULT_IP;
    their_addr.sin_family=AF_INET;
    their_addr.sin_port=htons((short)DEFAULT_PORT);
    inet_pton(AF_INET,serverAddress.c_str(),&their_addr.sin_addr);
    memset(&(their_addr.sin_zero),'\0',8);
}

client::client(string serverIP,int serverPort)
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
    //Configure the server address
    string serverAddress=serverIP;
    their_addr.sin_family=AF_INET;
    their_addr.sin_port=htons((short)serverPort);
    inet_pton(AF_INET,serverAddress.c_str(),&their_addr.sin_addr);
    memset(&(their_addr.sin_zero),'\0',8);
}


int client::initialize_client()
{
    connecting=connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr));
    if(connecting==-1)
    {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
        close(sockfd);
        return -1;
    }
    printf("Connected to %s in port %i \n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port));
    return 1;
}

int client::send_message(string message)
{
    char buffer[MAXBUFFERLEN];
    FILE *stream;
    int tn=message.size();
    char temp[tn+1];
    int num_char_read;
    strcpy(temp,message.c_str());
    stream=fmemopen(temp,strlen(temp),"r");
    num_char_read=fread(buffer+1,sizeof(char),sizeof(buffer),stream);
    buffer[0]=num_char_read;
    int sending=send(sockfd,(const char*)buffer,strlen(buffer)+1,0);
    if(sending==-1)
    {
        perror("Failure to send Package");
        exit(EXIT_FAILURE);
        close(sockfd);
        close(sockfd);
        return -1;
    }
    return 1;
}

string client::receive_message()
{
    char buffer[MAXBUFFERLEN];
    receiving=recv(sockfd,(char*)buffer,MAXBUFFERLEN,0);
    if(receiving==-1)
    {
        perror("Failed to received package");
        exit(EXIT_FAILURE);
        close(sockfd);
        close(sockfd);
    } 
    string temp(buffer);
    return temp;
    memset(buffer,'\0',MAXBUFFERLEN);
}

int client::closeSockets()
{
    close(sockfd);
    return 1;
}

#endif
