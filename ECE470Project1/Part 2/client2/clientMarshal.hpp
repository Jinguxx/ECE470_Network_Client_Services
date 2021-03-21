//
//  clientMessages.hpp
//  Project1SmartHome
//
//  Created by Jing Ma on 3/1/21.
//

#ifndef clientMarshal_hpp
#define clientMarshal_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;

class serverMessage
{
    public:
        string options;
        string message;
        vector<string> lines;
        int numlines;
    void print(){
            cout<<options<<"    "<<numlines<<"     "<<message<<endl;
            for(unsigned int i=0;i<lines.size();i++)
            {
                cout<<lines[i]<<endl;
            }
        }
};

class clientMessage
{
    public:
        string options;
        int choices;
    void print(){
            cout<<options<<"    "<<choices;
        }
};

serverMessage unmarshal(string message)
{
    string command;
    serverMessage res;
    stringstream ss(message);
    ss>>command;
    if(command=="USER")
    {   res.options="USER";
        getline(ss,res.message);
    }
    else if(command=="PASS")
    {
        res.options="PASS";
        getline(ss,res.message);
    }
    else if(command=="LIST")
    {
        res.options="LIST";
        getline(ss,res.message,'\\');
        ss>>res.numlines;
        vector<stringstream> tt(res.numlines);
        string temp;
        int i=0;
        while(ss>>temp)
        {
            if(res.message=="\\\\")
            {
                break;
            }
            else if(temp=="\\")
            {
                i++;
            }
            else
            {
                tt[i]<<temp<<" ";
            }
        }
        for(unsigned int j=0;j<tt.size();j++)
        {
            string temp2;
            getline(tt[j],temp2);
            res.lines.push_back(temp2);
        }
    }
    else if(command=="ERROR")
    {
        res.options="ERROR";
        getline(ss,res.message);
        ss>>res.message;
    }
    else if(command=="END")
    {
        res.options="END";
        getline(ss,res.message);
        ss>>res.message;
    }
    else
    {
    }
    return res;
}


string marshal(clientMessage clientM)
{
    stringstream ss;
    string result;
    if(clientM.options=="START")
    {
        ss<<clientM.options<<" "<<clientM.choices;
    }
    else if(clientM.options=="CHOICE")
    {
        ss<<clientM.options<<" "<<clientM.choices;
    }
    else if(clientM.options=="END")
    {
        ss<<clientM.options<<" "<<clientM.choices;
    }
    else if(clientM.options=="ERROR")
    {
        ss<<clientM.options<<" "<<clientM.choices;
    }
    else
    {
    }
    getline(ss,result);
    return result;
}

#endif /* clientMarshal_hpp */

