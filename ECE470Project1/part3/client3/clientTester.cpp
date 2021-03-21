//
//  clientTester.cpp
//  ECE470Project1
//
//  Created by Jing Ma on 3/2/21.
//

#include <stdio.h>
#include "TCP_client.h"
using namespace std;

int main(){
    client test;
    cout<<"Connection established..."<<endl;
    test.send_message("Messages are hard to send");
    test.send_message("My name is BLUE");
    test.send_message("Universityu of miami");
    test.send_message("end");
    test.closing_all();
    return 0;
}

