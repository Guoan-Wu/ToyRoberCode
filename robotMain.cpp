#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "robot.h"
using namespace std;

int main(int argc, char* argv[]){

    string filename = "./cmd/cmd1.txt";
    ifstream cmdfile(filename);
    vector<string> vLines;
    string line;
    
    int framecount = 1000;
    int iCount =0;
    int index =0;
    while(true){
        while(index < framecount && getline(cmdfile,line)){
            vLines.push_back(line);
            ++index;
        }

        //run robot
        iCount += index;

        if(index < framecount){//file read finished.
        cout << "Finshed all command (count:" << iCount <<"). Byebye!" << endl;
        return 0;
        } 
        index =0;
        vLines.clear();
    }

    return 0;
}