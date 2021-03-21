#include "server_marshal.h"
using namespace std;

int main(int argc,char*argv[]){
    
    if(argc<3){
        cout<<"Testing unmarshal"<<endl;
        client_message testing1 = unmarshal("START 2");
        testing1.printing();
    }
    else{
        
        cout<<"Testing Marshal"<<endl;
        server_message testing2;
        testing2.command=argv[1];
        testing2.messa=argv[2];
        testing2.num_lines=atoi(argv[3]);
        testing2.lines.push_back(argv[4]);
        testing2.lines.push_back(argv[5]);
        if(argc > 5){
            testing2.lines.push_back(argv[6]);
        }
        cout<<marshal(testing2)<<endl<<endl;
    }
    return 0;
}
