//
//  datamodelHome.cpp
//  ECE470Project1
//
//  Created by Jing Ma on 3/13/21.
//

#include <stdio.h>
#include "datamodel.h"

home::home(){
    homeInitialSetup();
}

void home:: homeInitialSetup() {
    username = "admin"; //username setup
    password = "welcome"; //password setup
    alarmPIN = "1234"; // alarm PIN setup
    
    rooms.push_back("Bedroom1");//5 bedrooms setup
    rooms.push_back("Bedroom2");
    rooms.push_back("Bathroom");
    rooms.push_back("Living");
    rooms.push_back("Dining");
    
    locks.push_back("Lock1"); //4 locks setup
    locks.push_back("Lock2");
    locks.push_back("Lock3");
    locks.push_back("Lock4");


}

home::~home() {
    ;// TODO Auto-generated destructor stub
}


bool home::checkLogin(string user, string pass){ //checking to seeif user loging and password is correct
    bool login = false;
    if (username.compare(user)==0 && password.compare(pass)==0) {
        login = true;
    }
    return login;
    
}

light::light(){
    lightInitialSetup();
}

void light::lightInitialSetup(){
    
    Glights.push_back("Bedroom1 Lights");//Grouped lights setup
    Glights.push_back("Bedroom2 Lights");
    Glights.push_back("Bathroom Lights");
    Glights.push_back("Living Lights");
    Glights.push_back("Dining Lights");
    
}

light::~light(){
    ;// TODO Auto-generated destructor stub
}



string light::getLightsNames(){
    int i = 1;
    string x;
    vector<string>:: iterator it;
    vector<string> *ret = new vector<string>;
    for(it=lights.begin(); it!=lights.end(); ++it) {
            //(*ret)[to_string(i)] = it->first;
            i++;
        }
    //return ;//ret;
    
}

rooms::rooms(){
    roomInitialSetup();
}

void rooms::roomInitialSetup(){
    
    room.push_back("Bedroom1");//5 bedrooms setup
    room.push_back("Bedroom2");
    room.push_back("Bathroom");
    room.push_back("Living");
    room.push_back("Dining");
}

home::~home(){
    ;
}


