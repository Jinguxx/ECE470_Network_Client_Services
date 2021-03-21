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
        string roomName;
        int roomNumber;
        int numLights;
        room(string roomMa ,int ro);
        void setNumLightList();
        void changeAllLights();
        void changeSingleLights(int option);
};

void room::changeAllLights()
{
    for(unsigned int i=0;i<lits.size();i++)
    {
        lits[i].litstatus=!lits[i].litstatus;
    }
    setNumLightList();
}

void room::changeSingleLights(int option)
{
    lits[option].litstatus=!lits[option].litstatus;
    setNumLightList();
}


void room::setNumLightList(){
    vector<string> tempLight;
    for(unsigned int i=0;i<lits.size();i++)
    {
        stringstream ss;
        string lightSta;
        string temp;
        if(lits[i].litstatus)
        {
            lightSta="ON";
        }
        else
        {
            lightSta="OFF";
        }
        ss<<lits[i].name<<" : "<<lightSta;
        getline(ss,temp);
        tempLight.push_back(temp);
    }
    litsList=tempLight;
}
 
room::room(){
    light t1("Light 1",true);
    light t2("Light 2",true);
    light t3("Light 3",true);
    light t4("Light 4",true);
    lits.push_back(t1);
    lits.push_back(t2);
    lits.push_back(t3);
    lits.push_back(t4);
    roomName="Bedroom1";
    numLights = lits.size();
    roomNumber=1;
    setNumLightList();
}


room::room(string roomNa,int ro)
{
    roomNumber=ro;
    stringstream ss;
    string temp;
    ss<<roomNumber<<". "<<roomNa;
    getline(ss,temp);
    light t1("1. Light 1",true);
    light t2("2. Light 2",true);
    light t3("3 .Light 3",true);
    light t4("4. Light 4",true);
    lits.push_back(t1);
    lits.push_back(t2);
    lits.push_back(t3);
    lits.push_back(t4);
    roomName=temp;
    numLights=lits.size();
    setNumLightList();
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
    room livingroom("living Room",3);
    hr.push_back(bedroom);
    hr.push_back(bathroom);
    hr.push_back(livingroom);
    nRoom = hr.size();
    setRoomPlan();
}

void rooms::setRoomPlan(){
    for(unsigned int i=0;i<hr.size();i++)
    {
        roomPlan.push_back(hr[i].roomName);
    }
}

class alarmNetwork {
    
    private:
        bool alarmStatus;
        int alarmPin;
    
    public:
        alarmNetwork(){
            alarmStatus = true;
            alarmPin = 12345;
        };
        string name;
        void changeAlarmStatus(int opt){
            if(opt = alarmPin){
                alarmStatus = !alarmStatus;
            }
        }
        bool getAlarmStatus(){
            return alarmStatus;
        };
};



class lock
{
    public:
        string name;
        int code;
        bool status;
    lock();
    lock(string nam,bool stat,int codd); 
};

lock::lock()
{
    name="Main";
    code=12345;
    status=true;
}

lock::lock(string nam,bool stat,int codd)
{
    name=nam;
    code=codd;
    status=stat;
}

class locks
{
    private:
        int masterLock;
    public:
        vector<lock> llock;
        vector <string> locksList;
        int numLocks;
        int locksPIN = 8888;
        locks();
        void setLocksList();
        void changeAllLocks(int opt);
        void changeSingleLock(int option, int opt);
};

void locks::changeAllLocks(int opt)
{
    masterLock = locksPIN;
    if(opt==masterLock)
    {
    for(unsigned int i=0;i<llock.size();i++)
    {
        llock[i].status=!llock[i].status;
    }
    setLocksList();
    }
}

void locks::changeSingleLock(int option,int opt)
{
    if(opt==llock[option].code)
    {
    llock[option].status=!llock[option].status;
    setLocksList();
    }
}

locks::locks()
{   //remaking rooms setup
    lock ll1("1. Front Door",true,3441);
    lock ll2("2. Back Door",true,1234);
    lock ll3("3. Garage Door",true,7812);
    lock ll4("4. Side door",true,2232);
    lock ll5("5. Bedroom Closet Door",true,2131);
    llock.push_back(ll1);
    llock.push_back(ll2);
    llock.push_back(ll3);
    llock.push_back(ll4);
    llock.push_back(ll5);
    numLocks=llock.size();
    setLocksList();
}

void locks::setLocksList()
{
   vector<string> tempLock;
    for(unsigned int i=0;i<llock.size();i++)
    {
        stringstream ss;
        string lightSta;
        string temp;
        if(llock[i].status)
        {
            lightSta="ON";
        }
        else
        {
            lightSta="OFF";
        }
        ss<<llock[i].name<<" : "<<lightSta;
        getline(ss,temp);
        tempLock.push_back(temp);
    }
    locksList=tempLock;
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
        void setPassword(string newPassword);
        void setUsername(string newUsername);
        void setDeviceMenuList();
};

void smartHome::setDeviceMenuList()
{
    deviceMenuList.push_back("1. Check Status");
    deviceMenuList.push_back("2. Change Status");
    
}

smartHome::smartHome()
{
    setDeviceMenuList();
}

#endif