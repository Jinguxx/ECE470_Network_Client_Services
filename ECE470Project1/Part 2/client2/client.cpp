//
//  clientMessages.cpp
//  Project1SmartHome
//
//  Created by Jing Ma on 3/1/21.
//

#include "clientMarshal.hpp"

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;



int main(int argc,char*argv[])
{

    if(argc ==2){
        
        cout<<"Testing unmarshal"<<endl;
        serverMessage testing2;
        testing2 = unmarshal( "USER Enter Your Username:");
        testing2.print();
    }

    if(argc>2)
    {
        cout<<"Testing Marshall"<<endl;
        clientMessage testing1;
        testing1.choices = atoi(argv[2]);
        testing1.options= argv[1];
        cout<<marshal(testing1)<<endl;
    }
return 0;
}

