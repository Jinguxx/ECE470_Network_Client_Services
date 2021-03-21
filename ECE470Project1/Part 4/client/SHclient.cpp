#include <iostream>
#include "tcp_client4.h"
#include "clientMarshal4.h"
using namespace std;

int main(){

    int userInput;
    //Start Client
    client test;
    test.initialize_client();
    //Creating sample client message
    clientMessage starting;
    starting.options="START";
    starting.choice=1;

    //Marshal the client message
    string sendMessage=marshal(starting);
    //Send starting message
    test.send_message(sendMessage);
    while(true){

        string recMessage;
        string sendingMessage;
        //Receive message
        recMessage=test.receive_message();
        serverMessage servMessage;
        //Unmarshall the message
        servMessage=unmarshal(recMessage);
        //Print the Message
        servMessage.printing();
        if(servMessage.options=="END"){

            break;
        }
        //Ask the user for input
        cin>>userInput;
        clientMessage userChoice;
        userChoice.options="CHOICE";
        userChoice.choice=userInput;
        sendingMessage=marshal(userChoice);
        test.send_message(sendingMessage);
    }
    test.closeSockets();
    return 0;
}