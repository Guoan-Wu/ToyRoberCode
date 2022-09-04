#include "robotMgr.h"
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    string filename{};
    //opt.
     int c = 0; 
    //read each option and its params.
    while(EOF != (c = getopt(argc,argv,"hi:")))
    {
        switch(c)
        {
            case 'h':{
                string shelp = "robotMain [-i <filename>]\n"
                        "Examples:\n"
                        "robotMain //input is cin.\n"
                        "robotMain -i ./cmd1.txt //input file name is ./cmd1.txt that includes commands to run the robot.\n"
                        "robotMain ./cmd1.txt //same to the above.";
                cout << shelp << endl; 
                return 0;                           
                break;
            }
            //-i: input, following command filename.
            case 'i':
                cout << "Command filename is: " << optarg << endl;
                filename = optarg;
                break;
            //unsupported option.
            case '?':
                cout << "unknow option:" << optopt <<endl;
                break;
            default:
                break;
        }   
    } 
    //filename but lacking -i.
    if(argc == 2) filename = argv[1];

    RobotMgr mgr;
    //filename//"./cmd/cmd1.txt";
    if(filename.size() >0){
        ifstream cmdfile(filename);
        if(cmdfile.fail()){
            cout << filename << " open fail" << endl;
            return -1;
        }
            
        cout << "Start run commands in the file..." << endl;
        return mgr.run(cmdfile,cout,100);
    } else {
        cout << "Please input commands one by one. \n" << 
        "E.g., PLACE 1,1,NORTH MOVE LEFT RIGHT REPORT." << endl;
        cout << "Please type quit if you want to quit the app." << endl;
        return mgr.run(cin,cout,1);
    }
    return 0;    
}