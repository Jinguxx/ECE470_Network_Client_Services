//
//  testingServer.cpp
//  ECE470Project1
//
//  Created by Jing Ma on 3/3/21.
//

#include <stdio.h>
#include "TCP_client.h"
using namespace std;

int main()
{
client test;
cout<<test.receive_message()<<endl;
test.closing_all();
return 0;
}
