#ifndef _SERVER_MARSHAL_H_
#define _SERVER_MARSHAL_H_
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;

class clientMessage{

    public:
    string command;
    int choice;
    void printing()
    {
        cout<<command<<"    "<<choice<<endl;
    }
};

class serverMessage{

    public:
        string command;
        string msg;
        vector<string> lines;
        int numlines;
};

class sample1{

    public:
    serverMessage usernameResponse;
    serverMessage passwordResponse;
    sample1(){

            create_passwordResponse();
            create_usernameResponse();
    }
    serverMessage create_usernameResponse(){

        usernameResponse.command="USER";
        usernameResponse.msg="Please Enter your username:";
        return usernameResponse;
    };

    serverMessage create_passwordResponse(){

        passwordResponse.command="PASS";
        passwordResponse.msg="Please Enter your password:";
        return passwordResponse;
    };

};


clientMessage unmarshal(string message){

    string command;
    int decision;
    clientMessage res;
    istringstream ss(message);
    ss>>command>>decision;
    res.command=command;
    res.choice=decision;
    return res;
}

string marshal(serverMessage serverM){
        
    stringstream ss;
    string result;
    string x[5]={"USER","PASS","LIST","ERROR","END"};
    if(serverM.command == x[0]){

        ss<<serverM.command<<" "<<serverM.msg<<" ";
    }
    else if(serverM.command == x[1]){

        ss<<serverM.command<<" "<<serverM.msg<<" ";
    }
    else if(serverM.command == x[2]){

        ss<<serverM.command<<" "<<serverM.msg<<" "<<"\\"<<" "<<serverM.numlines;
        for(int i=0;i<serverM.numlines;i++){

            ss<<" "<<serverM.lines[i]<<" "<<"\\";
        }
    }
    else if(serverM.command == x[3]){

        ss<<serverM.command<<" "<<serverM.msg;
    }
    else if(serverM.command == x[4]){

        ss<<serverM.command<<" "<<serverM.msg;
    }
    else{
    }
    getline(ss,result);
    return result;
}
#endif

