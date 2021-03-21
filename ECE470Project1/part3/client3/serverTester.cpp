//
//  serverTester.cpp
//  ECE470Project1
//
//  Created by Jing Ma on 3/2/21.
//

#include <stdio.h>
#include "TCP_client.h"
using namespace std;

int main()
{
    cout<<"Listening...waiting to be connected"<<endl;
    client test;
    cout<<"Starting..."<<endl;
    string temp="follow";
    while (temp!="end"){
        
        temp=test.receive_message();
        cout<<temp<<endl;
    }
    test.closing_all();
    return 0;
}

