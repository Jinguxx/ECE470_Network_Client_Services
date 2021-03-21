//
//  smartHomeServer.h
//  ECE470Project1
//
//  Created by Jing Ma on 3/17/21.
//

#ifndef smartHomeServer_h
#define smartHomeServer_h
#include <iostream>
#include <string>
#include "server_marshal.h"
#include "TCP_server.h"
#include "datamodel.h"


smartHome sample; //making an istance of home from datamodel.h

//Device Control Menu ------------------------------------------------

serverMessage deviceLists(){
    
    vector<string> temp = sample.deviceMenuList;
    temp.push_back("4. Return to Main");
    serverMessage deviceListMsg; //creating an instance of serverMessage called deviceListMsg
    deviceListMsg.command = "LIST";
    deviceListMsg.msg = "Device Control Menu ";
    deviceListMsg.numlines = temp.size();
    deviceListMsg.lines = temp;
    return deviceListMsg;
    
}


//Device Control Menu ------------------------------------------------


//Room Plan ----------------------------------------------------------

serverMessage roomsList()
{
    vector<string> temp = sample.nr.roomPlan;
    int tempNum = sample.nr.recNumRooms();
    stringstream ss;
    string tempAA;
    ss<<tempNum+1<<". "<<"Return to Menu";
    getline(ss,tempAA);
    temp.push_back(tempAA);
    serverMessage roomPlanMsg;
    roomPlanMsg.command="LIST";
    roomPlanMsg.msg="List of Rooms";
    roomPlanMsg.numlines = temp.size();
    roomPlanMsg.lines = temp;
    return roomPlanMsg;
}

//Room Plan ----------------------------------------------------------

//Locks Plan _________________________________________________________

serverMessage listsLock(int option)// need to remane variable add comments
{
    vector<string> temp=sample.lo.locksList;
    int tempNum=sample.lo.numLocks;
    stringstream ss;
    if(option==1)
    {
        stringstream ss1;
        string tempAA1;
        tempNum++;
        ss1<<tempNum<<". "<<"Change the status of all the locks";
        getline(ss1,tempAA1);
        temp.push_back(tempAA1);
    }
    string tempAA;
    ss<<tempNum+1<<". "<<"Return to Menu";
    getline(ss,tempAA);
    temp.push_back(tempAA);
    serverMessage listsLockMess;
    listsLockMess.command="LIST";
    listsLockMess.msg="Welcome to Locks";
    listsLockMess.numlines=temp.size();
    listsLockMess.lines=temp;
    return listsLockMess;
}

//Locks Plan __________________________________________________________


//Light Plan ---------------------------------------------------------


serverMessage lightList(int option1)
{
    vector<string> temp = sample.nr.hr[option1-1].litsList;
    int tempNum = sample.nr.hr[option1-1].numLights;
    stringstream ss;
    stringstream ss1;
    string tempAA1;
    tempNum++;
    ss1<<tempNum<<". "<<"Change the status of all lights";
    getline(ss1,tempAA1);
    temp.push_back(tempAA1);
    string tempAA;
    ss<<tempNum+1<<". "<<"Return to Menu";
    getline(ss,tempAA);
    temp.push_back(tempAA);
    serverMessage lightPlanMsg;
    lightPlanMsg.command="LIST";
    lightPlanMsg.msg = sample.nr.hr[option1-1].roomName;
    lightPlanMsg.numlines=temp.size();
    lightPlanMsg.lines=temp;
    return lightPlanMsg;
}

//Light Plan ----------------------------------------------------------


//Lights Menu ---------------------------------------------------------

int lightsMenu(server test, int option){
    
    string userInput;
   serverMessage lightsMenuMsg; 
    
    while(true)
    {
        
        lightsMenuMsg = lightList(option);
        string mainLightMenuMsg = marshal(lightsMenuMsg);
        int tempNum = sample.nr.hr[option-1].numLights;
        test.send_message(mainLightMenuMsg);
        userInput=test.receive_message();
        clientMessage tempMessage;
        tempMessage=unmarshal(userInput);
        if(tempMessage.choice==(tempNum+2))
        {
            break;
        }
        else if(tempMessage.choice==(tempNum+1))
        {
            sample.nr.hr[option-1].changeAllLights();
        }
        else if(tempMessage.choice==1)
        {
            sample.nr.hr[option-1].changeSingleLights(0);
        }
        else if(tempMessage.choice==2)
        {
            sample.nr.hr[option-1].changeSingleLights(1);
        }
        else if(tempMessage.choice==3)
        {
            sample.nr.hr[option-1].changeSingleLights(2);
        }
        else if(tempMessage.choice==4)
        { 
            sample.nr.hr[option-1].changeSingleLights(3);
        }
    }
    return -1;

}

//Lights Menu ----------------------------------------------------------


//Rooms Menu -----------------------------------------------------------
int roomMenu(server test){

    string userInput;
    serverMessage roomMenuMsg;
    while(true){
    
        roomMenuMsg = roomsList();
        string mainRoomMenuMsg = marshal(roomMenuMsg);
        int tempNum = sample.nr.nRoom;
        test.send_message(mainRoomMenuMsg);
        userInput = test.receive_message();
        clientMessage tempMessage;
        tempMessage = unmarshal(userInput);
        if(tempMessage.choice==(tempNum+1))
        {
            break;
        }
        else if(tempMessage.choice==1)
        {
            int llLightMenu;
            llLightMenu = lightsMenu(test,1);
        }
        else if(tempMessage.choice==2)
        {
             int llLightMenu;
            llLightMenu = lightsMenu(test,2);

        }
        else if(tempMessage.choice==3)
        {
            int llLightMenu;
            llLightMenu = lightsMenu(test,3);
        }
    }
    return -1;
}

//Rooms Menu -----------------------------------------------------------

//Alarm Check Status ---------------------------------------------------

serverMessage alarmStatus(int option1)
{
    vector<string> temp;
    string tempAlarm;
    bool alarmStatuses = sample.as.getAlarmStatus();
    if(alarmStatuses)
    {
        tempAlarm="ON";
    }
    else
    {
        
        tempAlarm="OFF";
    }
    string alarmSt="Alarm";
    string temp1;
    stringstream ss;
    int number=1;
    ss<<number<<". "<<alarmSt<<number<<":"<<tempAlarm;
    getline(ss,temp1);
    temp.push_back(temp1);
    temp.push_back("2. Change the status");
    temp.push_back("4. Return to Main");
    serverMessage alarmStatusMessage;
    alarmStatusMessage.command="LIST";
    alarmStatusMessage.numlines=temp.size();
    alarmStatusMessage.msg = "Check Status: Alarm";
    alarmStatusMessage.lines=temp;
    return alarmStatusMessage;
}

//Alarm Check Status ---------------------------------------------------

//Alarm Menu -----------------------------------------------------------
int alarmMenu(server test, int option2){
    
    serverMessage options1;
    options1.command="LIST";
    options1.msg = "Enter Pin for Alarm";
    options1.numlines=1;
    options1.lines.push_back("3 Attempts");
    string maOptions1=marshal(options1);

    string userInput;
    //serverMessage deviceMenuMsg;
    serverMessage alarmMenuMsg;
    
    while(true){
        
        alarmMenuMsg = alarmStatus(option2);
        string mainAlarmMenu = marshal(alarmMenuMsg);
        test.send_message(mainAlarmMenu);
        userInput = test.receive_message();
        clientMessage tempMessage;
        tempMessage = unmarshal(userInput);
        if(tempMessage.choice == 2)//change alarm status
        {
            for(int i = 1; i < 4; i++){
                test.send_message(maOptions1);
                userInput=test.receive_message();
                tempMessage=unmarshal(userInput);
               if(tempMessage.choice = i){
                    sample.as.changeAlarmStatus(tempMessage.choice);
               }
            }
            
        }
        else if(tempMessage.choice == 4){
            
            break;
        }
    }
    return -1;

}
//Alarm Menu------------------------------------------------------------


//Locks Menu ------------------------------------------------------------
int lcoksMenu(server test,int option){
    
    string userInput;
    serverMessage options1;
    options1.command="LIST";
    options1.msg="Enter PIN for Lock";
    options1.numlines=1;
    options1.lines.push_back("Enter Integers only");
    string mainOption1 = marshal(options1);
    while(true)
    {
        serverMessage lockMenuMsg = listsLock(option);
        string mainLockMsg = marshal(lockMenuMsg);
        int tempNum = sample.lo.numLocks;
        test.send_message(mainLockMsg);
        userInput=test.receive_message();
        clientMessage tempMessage;
        tempMessage=unmarshal(userInput);
        if(tempMessage.choice==(tempNum+1))//function used to change status of all locks
        {
            test.send_message(mainOption1);
            userInput=test.receive_message();
            tempMessage=unmarshal(userInput);
            sample.lo.changeAllLocks(tempMessage.choice);
        }
        else if(tempMessage.choice==(tempNum+2))//skips the option to change menuto exi menu
        {
            break;
        }
        else if(tempMessage.choice==1) //changes fron door
        {
            test.send_message(mainOption1);
            userInput=test.receive_message();
            tempMessage=unmarshal(userInput);
            sample.lo.changeSingleLock(0, tempMessage.choice);
        }
        else if(tempMessage.choice==2)//changes back door
        {
            test.send_message(mainOption1);
            userInput=test.receive_message();
            tempMessage=unmarshal(userInput);
            sample.lo.changeSingleLock(1, tempMessage.choice);
        }
        else if(tempMessage.choice==3)//changes garage door
        {
            test.send_message(mainOption1);
            userInput=test.receive_message();
            tempMessage=unmarshal(userInput);
            sample.lo.changeSingleLock(2, tempMessage.choice);
        }
        else if(tempMessage.choice==4)//changes side door
        {
            test.send_message(mainOption1);
            userInput=test.receive_message();
            tempMessage=unmarshal(userInput);
            sample.lo.changeSingleLock(3, tempMessage.choice);
        }
        else if(tempMessage.choice==5)//change bedroom closet
        {
            test.send_message(mainOption1);
            userInput=test.receive_message();
            tempMessage=unmarshal(userInput);
            sample.lo.changeSingleLock(4, tempMessage.choice);
        }
    }
    return -1;

}

//Locks Menu ---------------------------------------------------------

//Main menu ----------------------------------------------------------
int mainMenu(server test)
{
    string mainMenu;
    serverMessage cm;
    cm.command="LIST";
    cm.msg = "Main Menu";
    cm.numlines = 4;
    cm.lines.push_back("1. Lights");
    cm.lines.push_back("2. Alarms");
    cm.lines.push_back("3. Locks");
    cm.lines.push_back("4. Logout");
    mainMenu=marshal(cm);
    serverMessage ending;
    ending.command="END";
    ending.msg="Logged Out Complete";
    string mainEnding = marshal(ending);

    serverMessage options1;
    options1.command = "LIST";
    options1.msg = "Lights Entered";
    options1.numlines = 1;
    options1.lines.push_back("Lights Menu");
    string maOptions1 = marshal(options1);

    serverMessage options2;
    options2.command="LIST";
    options2.msg="Alarm Entered";
    options2.numlines=1;
    options2.lines.push_back("Alarm Menu");
    string maOptions2=marshal(options2);
    
    serverMessage options3;
    options2.command="LIST";
    options2.msg="Locks Entered";
    options2.numlines = 1;
    options2.lines.push_back("Locks Menu");
    string maOptions3 = marshal(options3);
    
    while(true) //main menu when login succeded
    {
        string userInput;
        test.send_message(mainMenu);
        clientMessage tempMessage;
        userInput=test.receive_message();
        tempMessage=unmarshal(userInput);
        if(tempMessage.choice == 1)
        {
             int menuLight;
            menuLight = roomMenu(test); //change
    
        }
        else if(tempMessage.choice == 2)
        {
           int menuAlarm;
           menuAlarm = alarmMenu(test,1); //change
        }
        else if(tempMessage.choice == 3){
            int menuLocks;
            menuLocks = lcoksMenu(test,1); //change

        }
        else if(tempMessage.choice == 4)
        {
            test.send_message(mainEnding);
            break;
        }
    }
    return -1;
}

//Main Menu ----------------------------------------------------------

#endif /* smartHomeServer_h */
