#ifndef _DATAMODEL_H_
#define _DATAMODEL_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class light 
{
    public:
        light();
        string name;
        bool litstatus;
        light(string name,bool status);
};

light::light(){
    name = "Bedroom1 Light";
    litstatus = true;
    
}

light::light(string name1, bool status1){
    name = name1;
    litstatus = status1;
}

class room{
    public:
        room();
        vector<light> lits;
        vector<string> litsList;
        string nameOfRoom;
        int roomNum;
        int numLights;
        room(string roomMa ,int ro);
        void setNumLightPlan();
        void changeAllLights();
        void changeSingleLights(int option);
};

void room::changeAllLights()
{
    for(unsigned int i=0;i<lits.size();i++)
    {
        lits[i].litstatus=!lits[i].litstatus;
    }
    setNumLightPlan();
}

void room::changeSingleLights(int option)
{
    lits[option].litstatus=!lits[option].litstatus;
    setNumLightPlan();
}


void room::setNumLightPlan(){
    vector<string> lightTemp;
    for(unsigned int i=0;i<lits.size();i++)
    {
        stringstream ss;
        string statLight;
        string temp;
        if(lits[i].litstatus)
        {
            statLight="ON";
        }
        else
        {
            statLight="OFF";
        }
        ss<<lits[i].name<<" : "<<statLight;
        getline(ss,temp);
        lightTemp.push_back(temp);
    }
    litsList=lightTemp;
}
 
room::room(){
    light lamp1("Light 1",true);
    light lamp2("Light 2",true);
    light lamp3("Light 3",true);
    light lamp4("Light 4",true);
    lits.push_back(lamp1);
    lits.push_back(lamp2);
    lits.push_back(lamp3);
    lits.push_back(lamp4);
    nameOfRoom="Bedroom1";
    numLights = lits.size();
    roomNum=1;
    setNumLightPlan();
}


room::room(string roomNa,int ro)
{
    roomNum = ro;
    stringstream ss;
    string temp;
    ss<<roomNum<<". "<<roomNa;
    getline(ss,temp);
    light lazer1("1. Light 1",true);
    light lazer2("2. Light 2",true);
    light lazer3("3 .Light 3",true);
    light lazer4("4. Light 4",true);
    lits.push_back(lazer1);
    lits.push_back(lazer2);
    lits.push_back(lazer3);
    lits.push_back(lazer4);
    nameOfRoom=temp;
    numLights=lits.size();
    setNumLightPlan();
}


class rooms
{
    public:
        rooms();
        vector<room> hr;
        int nRoom;
        vector<string> roomPlan;
        int recNumRooms(){
            return nRoom;
        }
        void setRoomPlan();
};

rooms::rooms(){
    room bedroom("Master Bedroom",1);
    room bathroom("Bedroom 1",2);
    room livingroom("Living Room",3);
    hr.push_back(bedroom);
    hr.push_back(bathroom);
    hr.push_back(livingroom);
    nRoom = hr.size();
    setRoomPlan();
}

void rooms::setRoomPlan(){
    for(unsigned int i=0;i<hr.size();i++)
    {
        roomPlan.push_back(hr[i].nameOfRoom);
    }
}

class alarmNetwork {
    
    private:
        bool stateOfAlarm;
        int alarmPin;
    
    public:
        alarmNetwork(){
            stateOfAlarm = true;
        };
        int alarmPIN = 12345;
        string name;
        void changestateOfAlarm(int opt){
            if(opt == alarmPIN){
                stateOfAlarm =! stateOfAlarm;
            }
        }
        bool getstateOfAlarm(){
            return stateOfAlarm;
        };
};



class lock
{
    public:
        string lockName;
        int lockPIN;
        bool lockStatus;
    lock();
    lock(string nam,bool stat,int codd); 
};

lock::lock()
{
    lockName="Main";
    lockPIN=12345;
    lockStatus=true;
}

lock::lock(string nam,bool stat,int codd)
{
    lockName=nam;
    lockPIN=codd;
    lockStatus=stat;
}

class locks
{
    private:
        int masterKey;
    public:
        vector<lock> llock;
        vector <string> locksPlan;
        int numLocks;
        int locksPIN = 8888;
        locks();
        void setLockPlan();
        void changeLocksAll(int opt);
        void changeIndivLock(int option, int opt);
};

void locks::changeLocksAll(int opt)
{
    masterKey = locksPIN;
    if(opt==masterKey)
    {
    for(unsigned int i=0;i<llock.size();i++)
    {
        llock[i].lockStatus=!llock[i].lockStatus;
    }
    setLockPlan();
    }
}

void locks::changeIndivLock(int option,int opt)
{
    if(opt==llock[option].lockPIN)
    {
    llock[option].lockStatus=!llock[option].lockStatus;
    setLockPlan();
    }
}

locks::locks()
{   //remaking rooms setup
    lock loc1("1. Front Door",true,8264);
    lock loc2("2. Back Door",true,1842);
    lock loc3("3. Garage Door",true,3065);
    lock loc4("4. Side door",true,9538);
    lock loc5("5. Bedroom Closet Door",true,2131);
    llock.push_back(loc1);
    llock.push_back(loc2);
    llock.push_back(loc3);
    llock.push_back(loc4);
    llock.push_back(loc5);
    numLocks=llock.size();
    setLockPlan();
}

void locks::setLockPlan()
{
   vector<string> lockTemp;
    for(unsigned int i=0;i<llock.size();i++)
    {
        stringstream ss;
        string statLight;
        string temp;
        if(llock[i].lockStatus)
        {
            statLight="ON";
        }
        else
        {
            statLight="OFF";
        }
        ss<<llock[i].lockName<<" : "<<statLight;
        getline(ss,temp);
        lockTemp.push_back(temp);
    }
    locksPlan=lockTemp;
}


class smartHome{
    private:
        string username;
        string password;
        
    public:
        smartHome();
        rooms nr;
        alarmNetwork as;
        locks lo;
        vector<string> deviceMenuList;
        int user = 1956;
        int pass = 1234;
        void setPassword();
        void setUsername();
        void setDeviceMenuList();
};


void smartHome::setDeviceMenuList()
{
    deviceMenuList.push_back("1. Check Status");
    deviceMenuList.push_back("2. Change Status");
    
}

smartHome::smartHome(){
    setDeviceMenuList();
}

#endif