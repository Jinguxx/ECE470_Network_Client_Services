#ifndef _SERVER_MARSHAL_H_
#define _SERVER_MARSHAL_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;

class client_message
{
    public:
    string command;
    int decision;
    void printing()
    {
        cout<<command<<"    "<<decision<<endl;
    }
};

class server_message
{
    public:
        string command;
        string messa;
        vector<string> lines;
        int num_lines;
};

client_message unmarshal(string message)
{
    string command;
    int decision;
    client_message res;
    istringstream ss(message);
    ss>>command>>decision;
    res.command=command;
    res.decision=decision;
    return res;
}

string marshal(server_message sm)
{
stringstream ss;
string result;
string c[5]={"USER","PASS","LIST","ERROR","END"};
if(sm.command == c[0])
{
    ss<<sm.command<<" "<<sm.messa<<"\\";
}
else if(sm.command == c[1])
{
    ss<<sm.command<<" "<<sm.messa<<"\\";
}
else if(sm.command == c[2])
{
    ss<<sm.command<<" "<<sm.num_lines<<" "<<sm.messa<<"\\";
    for(int i=0;i<sm.num_lines;i++)
    {
        ss<<sm.lines[i]<<"\\";
    }
    ss<<"\\\\";
}
else if(sm.command == c[3])
{
    ss<<sm.command<<" "<<sm.messa;
}
else if(sm.command == c[4])
{
    ss<<sm.command<<" "<<sm.messa;
}
else
{
}
getline(ss,result);
return result;
}


#endif

