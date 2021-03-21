#ifndef _SERVER_MARSHAL_H_
#define _SERVER_MARSHAL_H_
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
    void printing()
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

class sample1
{
    public:
    serverMessage usernameResponse;
    serverMessage passwordResponse;
    sample1()
    {
            create_passwordResponse();
            create_usernameResponse();
    }
    serverMessage create_usernameResponse()
    {
        usernameResponse.command="USER";
        usernameResponse.msg="Please Enter your username:";
        return usernameResponse;
    };

    serverMessage create_passwordResponse()
    {
        passwordResponse.command="PASS";
        passwordResponse.msg="Please Enter your password:";
        return passwordResponse;
    };

};


clientMessage unmarshal(string message)
{
    string command;
    int decision;
    clientMessage res;
    istringstream ss(message);
    ss>>command>>decision;
    res.command=command;
    res.choice=decision;
    return res;
}

string marshal(serverMessage sm)
{
stringstream ss;
string result;
string c[5]={"USER","PASS","LIST","ERROR","END"};
if(sm.command == c[0])
{
    ss<<sm.command<<" "<<sm.msg<<" ";
}
else if(sm.command == c[1])
{
    ss<<sm.command<<" "<<sm.msg<<" ";
}
else if(sm.command == c[2])
{
    ss<<sm.command<<" "<<sm.msg<<" "<<"\\"<<" "<<sm.numlines;
    for(int i=0;i<sm.numlines;i++)
    {
        ss<<" "<<sm.lines[i]<<" "<<"\\";
    }
}
else if(sm.command == c[3])
{
    ss<<sm.command<<" "<<sm.msg;
}
else if(sm.command == c[4])
{
    ss<<sm.command<<" "<<sm.msg;
}
else
{
}
getline(ss,result);
return result;
}
#endif

