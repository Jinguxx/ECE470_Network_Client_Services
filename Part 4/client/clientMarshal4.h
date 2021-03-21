//
//  clientMessages.hpp
//  Project1SmartHome
//
//  Created by Jing Ma on 3/1/21.
//

#ifndef clientMarshal_h
#define clientMarshal_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;

class server_message
{
    public:
        string options;
        string message;
        vector<string> lines;
        int num_lines;
        void printingDebug()
        {
            cout<<options<<"    "<<num_lines<<"     "<<message<<endl;
            for(unsigned int i=0;i<lines.size();i++)
            {
                cout<<lines[i]<<endl;
            }
            
        }
        void printing()
        {
            cout<<message<<endl;
            for(unsigned int i=0;i<lines.size();i++)
            {
                cout<<lines[i]<<endl;
            }

        }
};

class client_message
{
    public:
        string options;
        int decision;
        void printing()
        {
            cout<<options<<"    "<<decision;
        }
};

server_message unmarshal(string message)
{
    string command;
    server_message res;
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
        ss>>res.num_lines;
        vector<stringstream> tt(res.num_lines);
        string temp;
        int i=0;
        while(ss>>temp)
        {
            if(temp=="\\")
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


string marshal(client_message cm)
{
    stringstream ss;
    string result;
    if(cm.options=="START")
    {
        ss<<cm.options<<" "<<cm.decision;
    }
    else if(cm.options=="CHOICE")
    {
        ss<<cm.options<<" "<<cm.decision;
    }
    else if(cm.options=="END")
    {
        ss<<cm.options<<" "<<cm.decision;
    }
    else if(cm.options=="ERROR")
    {
        ss<<cm.options<<" "<<cm.decision;
    }
    else
    {
    } 
    getline(ss,result);
    return result;
}


#endif /* clientMarshal_hpp */

