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

class serverMessage{

    public:
        string options;
        string msg;
        vector<string> lines;
        int numlines;
        void printingDebug(){

            cout<<options<<"    "<<numlines<<"     "<<msg<<endl;
            for(unsigned int i=0;i<lines.size();i++){

                cout<<lines[i]<<endl;
            }
        }
        void printing(){

            cout<<msg<<endl;
            for(unsigned int i=0;i<lines.size();i++){

                cout<<lines[i]<<endl;
            }
        }
};

class clientMessage{

    public:
        string options;
        int choice;
        void printing(){
        
            cout<<options<<"    "<<choice;
        }
};

serverMessage unmarshal(string message){

    string command;
    serverMessage res;
    stringstream ss(message);
    ss>>command;
    if(command=="USER"){
        
        res.options="USER";
        getline(ss,res.msg);
    }
    else if(command=="PASS"){

        res.options="PASS";
        getline(ss,res.msg);
    }
    else if(command=="LIST"){

        res.options="LIST";
        getline(ss,res.msg,'\\');
        ss>>res.numlines;
        vector<stringstream> tt(res.numlines);
        string tempSM;
        int i=0;
        while(ss>>tempSM){

            if(tempSM=="\\"){

                i++;
            }
            else{

                tt[i]<<tempSM<<" ";
            }
        }
        for(unsigned int j=0;j<tt.size();j++){

            string temp;
            getline(tt[j],temp);
            res.lines.push_back(temp);
        }
    }
    else if(command=="ERROR"){

        res.options="ERROR";
        getline(ss,res.msg);
        ss>>res.msg;
    }
    else if(command=="END"){

        res.options="END";
        getline(ss,res.msg);
        ss>>res.msg;
    }
    else{
    }
    return res;
}


string marshal(clientMessage clientM)
{
    stringstream ss;
    string result;
    if(clientM.options=="START"){

        ss<<clientM.options<<" "<<clientM.choice;
    }
    else if(clientM.options=="CHOICE"){

        ss<<clientM.options<<" "<<clientM.choice;
    }
    else if(clientM.options=="END"){

        ss<<clientM.options<<" "<<clientM.choice;
    }
    else if(clientM.options=="ERROR"){

        ss<<clientM.options<<" "<<clientM.choice;
    }
    else{
    } 
    getline(ss,result);
    return result;
}


#endif /* clientMarshal_hpp */

