//
//  smartHomeServer.cpp
//  ECE470Project1
//
//  Created by Jing Ma on 3/17/21.
//

#include <iostream>
#include "TCP_server.h"
#include "server_marshal.h"
#include "smartHomeServer.h"
using namespace std;
int main(){
    
    //server start up **************************************
    
    string recieveStartingMsg;
    server testing;//instance of server from TCP_serve.h, Initializing server
    testing.initialize_server(); //starting connection
    recieveStartingMsg = testing.receive_message();//recieving message
    clientMessage startingMsg;
    startingMsg = unmarshal(recieveStartingMsg); //unmarshaling the message reciving from the client
    
    if(startingMsg.command != "START"){ //check if you have the starting message from client
        testing.closeSockets();
        exit(EXIT_SUCCESS);
    }
    //*****************************************************

    //Login seetup ****************************************
    
    sample1 temp111;
    serverMessage userServMess;
    serverMessage passServMess;
    userServMess = temp111.usernameResponse;
    string userMessage = marshal(userServMess);
    //Password
    passServMess = temp111.passwordResponse;
    string passMessage = marshal(passServMess);
    string userInput;
    
    while(true){
        //Send username response
        testing.send_message(userMessage);//Receive User Response
        userInput = testing.receive_message();
        clientMessage tempUserMessage;
        tempUserMessage=unmarshal(userInput);
        //Send Password
        testing.send_message(passMessage);
        userInput = testing.receive_message();
        clientMessage tempPassMessage;
        tempPassMessage=unmarshal(userInput);//unmarshaling user input
        if(tempPassMessage.choice==45 && tempUserMessage.choice==7){//pass=45.User=7

            cout<<"Successfully logged in."<<endl;
            int mmMenu = mainMenu(testing); //opening menu
            
            if(mmMenu == -1){
                
            }
            testing.closeSockets(); //closes the socket

            break;
            }
        }
        
    //*****************************************************
    
    return 0;
}
