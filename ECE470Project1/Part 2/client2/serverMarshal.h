//
//  serverMessages.hpp
//  Project1SmartHome
//
//  Created by Jing Ma on 3/1/21.
//

#ifndef serverMarshal_h
#define serverMarshal_h

#include <stdio.h>

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;

class clientMessage
{
    public:
    string command;
    int choice;
    void print()
    {
        cout<<command<<"    "<<choice<<endl;
    }
};

class serverMessage
{
    public:
        string command;
        string msg;
        vector<string> lines;
        int numlines;
};

clientMessage unmarshal(string message)
{
    string command;
    int choice;
    clientMessage res;
    istringstream ss(message);
    ss>>command>>choice;
    res.command=command;
    res.choice=choice;
    return res;
}

string marshal(serverMessage serveM){
    
    stringstream ss;
    string result;
    string c[5]={"USER","PASS","LIST","ERROR","END"};
    if(serveM.command == c[0]){
        ss<<serveM.command<<" "<<serveM.msg<<"\\";
    }
    
    else if(serveM.command == c[1]){
        ss<<serveM.command<<" "<<serveM.msg<<"\\";
    }
    
    else if(serveM.command == c[2]){
        ss<<serveM.command<<" "<<serveM.numlines<<" "<<serveM.msg<<"\\";
        
        for(int i=0;i<serveM.numlines;i++){
            ss<<serveM.lines[i]<<"\\";
        }
        ss<<"\\\\";
    }
    
    else if(serveM.command == c[3]){
        ss<<serveM.command<<" "<<serveM.msg;
    }
    
    else if(serveM.command == c[4]){
        ss<<serveM.command<<" "<<serveM.msg;
    }
    
    else{
    }
   
    getline(ss,result);
    return result;
}

#endif /* serverMarshal_h */
