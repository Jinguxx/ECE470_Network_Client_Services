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
    smartHome smartSet; //instance of class smartHome
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
    //----------------------------------------------------------------------

    //Login seetup ---------------------------------------------------------
    
    sample1 temp111;
    serverMessage userServerMsg;
    serverMessage passServerMsg;
    userServerMsg = temp111.usernameResponse; //username
    string userMessage = marshal(userServerMsg); 
    passServerMsg = temp111.passwordResponse; //password
    string passMessage = marshal(passServerMsg);
    string userInput;//getting user input
    
    while(true){
       
        testing.send_message(userMessage); //sending username 
        userInput = testing.receive_message(); //Receiving User 
        clientMessage tempUserMessage;
        tempUserMessage=unmarshal(userInput);
        //Send Password
        testing.send_message(passMessage);
        userInput = testing.receive_message();
        clientMessage tempPassMessage;
        tempPassMessage=unmarshal(userInput);//unmarshaling user input
        if((tempPassMessage.choice = smartSet.pass) && (tempUserMessage.choice = smartSet.user)){

            cout<<"Successfully logged in."<<endl;
            int mmMenu = mainMenu(testing); //opening menu
            
            if(mmMenu == -1){
                
                testing.closeSockets(); //closes the socket
                break;
            }    
        }
    }
    return 0;
}
