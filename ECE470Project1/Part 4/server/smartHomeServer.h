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


//Room List ----------------------------------------------------------

serverMessage roomsList(){ //function used as the bilding block of the rooms menu

    vector<string> temp = sample.nr.roomPlan;
    int roomTempNum = sample.nr.recNumRooms();
    stringstream ss;
    string roomTempA;
    ss<<roomTempNum+1<<". "<<"Return to Menu";
    getline(ss,roomTempA);
    temp.push_back(roomTempA);
    serverMessage roomPlanMsg;
    roomPlanMsg.command="LIST";
    roomPlanMsg.msg="List of Rooms";
    roomPlanMsg.numlines = temp.size();
    roomPlanMsg.lines = temp;
    return roomPlanMsg;
}

//Room List ----------------------------------------------------------

//Locks Plan _________________________________________________________

serverMessage listsLock(int option){//function will be the bulding block for the lock menu

    vector<string> temp=sample.lo.locksPlan;
    int lockTempNum = sample.lo.numLocks;
    stringstream ss;

    if(option==1){

        stringstream ss1;
        string lockTemp1;
        lockTempNum++;
        ss1<<lockTempNum<<". "<<"Change the status of all the locks";
        getline(ss1,lockTemp1);
        temp.push_back(lockTemp1);
    }
    string lockTempA;
    ss<<lockTempNum+1<<". "<<"Return to Menu";
    getline(ss,lockTempA);
    temp.push_back(lockTempA);
    serverMessage listsLockMess;
    listsLockMess.command="LIST";
    listsLockMess.msg="Welcome to Locks";
    listsLockMess.numlines=temp.size();
    listsLockMess.lines=temp;
    return listsLockMess;
}

//Locks Plan __________________________________________________________


//Light Plan ---------------------------------------------------------


serverMessage lightList(int option1){//function used as the bulding blocks of the lights menu

    vector<string> temp = sample.nr.hr[option1-1].litsList;
    int lightTempNum = sample.nr.hr[option1-1].numLights;
    stringstream ss;
    stringstream ss1;
    string lightTemp1;
    lightTempNum++;
    ss1<<lightTempNum<<". "<<"Change the status of all lights";
    getline(ss1,lightTemp1);
    temp.push_back(lightTemp1);
    string lightTempA;
    ss<<lightTempNum+1<<". "<<"Return to Menu";
    getline(ss,lightTempA);
    temp.push_back(lightTempA);
    serverMessage lightPlanMsg;
    lightPlanMsg.command="LIST";
    lightPlanMsg.msg = sample.nr.hr[option1-1].nameOfRoom;
    lightPlanMsg.numlines=temp.size();
    lightPlanMsg.lines=temp;
    return lightPlanMsg;
}

//Light Plan ----------------------------------------------------------


//Lights Menu ---------------------------------------------------------

int lightsMenu(server test, int option){// implementation using light function to create a lights menu
    
    string userInput;//taking in user input
   serverMessage lightsMenuMsg; //instance of serverMessage, initializing the connection
    
    while(true){//while loop to loop through menu choices
        
        lightsMenuMsg = lightList(option);
        string mainLightMenuMsg = marshal(lightsMenuMsg);
        int lightTempNum = sample.nr.hr[option-1].numLights;
        test.send_message(mainLightMenuMsg);
        userInput=test.receive_message();
        clientMessage messageTempLight;
        messageTempLight=unmarshal(userInput);

        if(messageTempLight.choice==(lightTempNum+2)){ //used to leave current menu, go backward to the last menu

            break;
        }
        else if(messageTempLight.choice==(lightTempNum+1)){ //if choice is 5, change all light status

            sample.nr.hr[option-1].changeAllLights();
        }
        else if(messageTempLight.choice==1){// if choice is 1 change light 1

            sample.nr.hr[option-1].changeSingleLights(0);
        }
        else if(messageTempLight.choice==2){//if choice is 2, change light 2

            sample.nr.hr[option-1].changeSingleLights(1);
        }
        else if(messageTempLight.choice==3){//if choice is 3, change light 3

            sample.nr.hr[option-1].changeSingleLights(2);
        }
        else if(messageTempLight.choice==4){//if choice 4, change light 3

            sample.nr.hr[option-1].changeSingleLights(3);
        }
    }
    return -1;

}

//Lights Menu ----------------------------------------------------------


//Rooms Menu -----------------------------------------------------------
int roomMenu(server test){ //implementation of the previous room function to create room menu

    string userInput;  //intaking user input
    serverMessage roomMenuMsg;//instance of server message
    while(true){//while loop to loop through menu choices
    
        roomMenuMsg = roomsList();
        string mainRoomMenuMsg = marshal(roomMenuMsg);
        int roomTempNum = sample.nr.nRoom;
        test.send_message(mainRoomMenuMsg);
        userInput = test.receive_message();
        clientMessage messageTempRoom;
        messageTempRoom = unmarshal(userInput);
        if(messageTempRoom.choice==(roomTempNum+1)){ //if choice 4, return to previous menu

            break;
        }
        else if(messageTempRoom.choice==1){// if choice 1 go to room 1

            int roomLightMenu;
            roomLightMenu = lightsMenu(test,1);
        }
        else if(messageTempRoom.choice==2){//if choice 2 go to room 2

            int roomLightMenu;
            roomLightMenu = lightsMenu(test,2);
        }
        else if(messageTempRoom.choice==3){//if choice 3 go to room 3

            int roomLightMenu;
            roomLightMenu = lightsMenu(test,3);
        }
    }
    return -1;
}

//Rooms Menu -----------------------------------------------------------

//Alarm Check Status ---------------------------------------------------

serverMessage alarmStatus(int option1){ //function used to create the alarm menu 

    vector<string> temp; //vector of string named temp
    string subAlarm;
    bool alarmStat = sample.as.getstateOfAlarm();
    if(alarmStat){

        subAlarm="ON";
    }
    else{
      
        subAlarm="OFF";
    }
    string alarmSt="Alarm";
    string temp1;
    stringstream ss;
    int number = 1;
    ss<<number<<". "<<alarmSt<<number<<":"<<subAlarm;
    getline(ss,temp1);
    temp.push_back(temp1);
    temp.push_back("2. Change Alarm Status");
    temp.push_back("4. Return to Main");
    serverMessage alarmStatMsg;
    alarmStatMsg.command="LIST";
    alarmStatMsg.numlines=temp.size();
    alarmStatMsg.msg = "Check Status: Alarm";
    alarmStatMsg.lines=temp;
    return alarmStatMsg;
}

//Alarm Check Status ---------------------------------------------------

//Alarm Menu -----------------------------------------------------------
int alarmMenu(server test, int option2){
    
    serverMessage opt; //instance of server message
    alarmNetwork alarmN; //instance of class alarmNetwork
    opt.command="LIST";
    opt.msg = "Enter Pin for Alarm";
    opt.numlines = 1;
    opt.lines.push_back("Only Integers Allowed");
    string alarmDecision = marshal(opt);

    string userInput; //taking in user iput
    serverMessage alarmMenuMsg;
    
    while(true){//while loop to loop through menu choices
        
        alarmMenuMsg = alarmStatus(option2);
        string mainAlarmMenu = marshal(alarmMenuMsg);
        test.send_message(mainAlarmMenu);
        userInput = test.receive_message(); 
        clientMessage messageTemp;
        messageTemp = unmarshal(userInput);
        if(messageTemp.choice == 2){//change alarm status

            test.send_message(alarmDecision);
            userInput=test.receive_message();
            messageTemp=unmarshal(userInput);
            sample.as.changestateOfAlarm(messageTemp.choice);
            
        }
        else if(messageTemp.choice == 4){
            
            break;
        }
    }
    return -1;

}
//Alarm Menu------------------------------------------------------------


//Locks Menu ------------------------------------------------------------
int lcoksMenu(server test,int option){  //function for locks menu
    
    string userInput;
    serverMessage lockDecision;
    lockDecision.command = "LIST";
    lockDecision.msg = "Enter PIN for Lock";
    lockDecision.numlines = 1;
    lockDecision.lines.push_back("Enter Integers only");
    string mainOption1 = marshal(lockDecision);
    while(true){ //while loop to loop through menu choices

        serverMessage lockMenuMsg = listsLock(option);
        string mainLockMsg = marshal(lockMenuMsg);
        int lockTempNum = sample.lo.numLocks;
        test.send_message(mainLockMsg);
        userInput = test.receive_message();
        clientMessage messageTempLock;
        messageTempLock = unmarshal(userInput);
        if(messageTempLock.choice == (lockTempNum+1)){ //function used to change status of all locks
        
            test.send_message(mainOption1);
            userInput=test.receive_message();
            messageTempLock=unmarshal(userInput);
            sample.lo.changeLocksAll(messageTempLock.choice);
        }
        else if(messageTempLock.choice==(lockTempNum+2)){ //skips the option to change menuto exi menu

            break;
        }
        else if(messageTempLock.choice==1){ //changes front door

            test.send_message(mainOption1);
            userInput=test.receive_message();
            messageTempLock=unmarshal(userInput);
            sample.lo.changeIndivLock(0, messageTempLock.choice);
        }
        else if(messageTempLock.choice==2){//changes back door

            test.send_message(mainOption1);
            userInput=test.receive_message();
            messageTempLock=unmarshal(userInput);
            sample.lo.changeIndivLock(1, messageTempLock.choice);
        }
        else if(messageTempLock.choice==3){//changes garage door
        
            test.send_message(mainOption1);
            userInput=test.receive_message();
            messageTempLock=unmarshal(userInput);
            sample.lo.changeIndivLock(2, messageTempLock.choice);
        }
        else if(messageTempLock.choice==4){//changes side door
        
            test.send_message(mainOption1);
            userInput=test.receive_message();
            messageTempLock=unmarshal(userInput);
            sample.lo.changeIndivLock(3, messageTempLock.choice);
        }
        else if(messageTempLock.choice==5){//change bedroom closet
        
            test.send_message(mainOption1);
            userInput=test.receive_message();
            messageTempLock=unmarshal(userInput);
            sample.lo.changeIndivLock(4, messageTempLock.choice);
        }
    }
    return -1;

}

//Locks Menu ---------------------------------------------------------

//Main menu ----------------------------------------------------------
int mainMenu(server test){//creating main menu for the program

    string mainMenu;
    serverMessage mainmenu; //instance of server messsage
    mainmenu.command="LIST";
    mainmenu.msg = "Main Menu";
    mainmenu.numlines = 4;
    mainmenu.lines.push_back("1. Lights");//menu options 
    mainmenu.lines.push_back("2. Alarms");
    mainmenu.lines.push_back("3. Locks");
    mainmenu.lines.push_back("4. Logout");
    mainMenu=marshal(mainmenu);
    serverMessage ending;
    ending.command="END";
    ending.msg="Logged Out Complete";//ending messsage when choice 4 is pressed
    string mainEnding = marshal(ending);

    serverMessage options1;
    options1.command = "LIST";
    options1.msg = "Lights Entered";
    options1.numlines = 1;
    options1.lines.push_back("Lights Menu");
    string mmDecision1 = marshal(options1);

    serverMessage options2;
    options2.command="LIST";
    options2.msg="Alarm Entered";
    options2.numlines=1;
    options2.lines.push_back("Alarm Menu");
    string mmOptions2=marshal(options2);
    
    serverMessage options3;
    options3.command="LIST";
    options3.msg="Locks Entered";
    options3.numlines = 1;
    options3.lines.push_back("Locks Menu");
    string mmOptions3 = marshal(options3);
    
    while(true){ //main menu when login succeded

        string userInput;
        test.send_message(mainMenu);
        clientMessage messageTempMain;
        userInput=test.receive_message();
        messageTempMain=unmarshal(userInput);
        if(messageTempMain.choice == 1){ //choice 1 lights menu

             int menuLight;
            menuLight = roomMenu(test); 
    
        }
        else if(messageTempMain.choice == 2){ //choice 2 alarm menu

           int menuAlarm;
           menuAlarm = alarmMenu(test,1); 
        }
        else if(messageTempMain.choice == 3){ //choice 3 locks menu
            int menuLocks;
            menuLocks = lcoksMenu(test,1); 

        }
        else if(messageTempMain.choice == 4){ //choice 4 logout

            test.send_message(mainEnding);
            break;
        }
    }
    return -1;
}

//Main Menu ----------------------------------------------------------

#endif /* smartHomeServer_h */
