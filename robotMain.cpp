#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include "robot.h"
using namespace std;
class Report
{
private:
    /* data */
public:
    Report(/* args */){}
    ~Report(){}
    void reportResult(const RobotCmd & cmd){
        cout << cmd << endl;
    }
};

// int main(int argc, char* argv[]){
//     string filename = "./cmd/cmd1.txt";
//     ifstream cmdfile(filename);
//     vector<string> vLines;
//     string line;
//     Robot rbt(5);
//     Report reportObj;
//     rbt.SetReportFunc(bind(&Report::reportResult,&reportObj,placeholders::_1));
    
//     int framecount = 1000;
//     int iCount =0;
//     int index =0;
//     while(true){
//         while(index < framecount && getline(cmdfile,line)){
//             for_each(line.begin(),line.end(),::toupper);//upper.
//             vLines.push_back(line);
//             ++index;
//         }

//         //run robot
//         iCount += index;
//         if( rbt.runCommand(vLines) < 0){
//             cout << "Robot run command error!" << endl;
//             return EXIT_FAILURE;
//         }
//         if(index < framecount){//file read finished.
//         cout << "Finshed all command (count:" << iCount <<"). Byebye!" << endl;
//         return 0;
//         } 
//         index =0;
//         vLines.clear();
//     }

//     return 0;
// }