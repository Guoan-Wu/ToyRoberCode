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
        cout << "Report robot's position " << cmd << endl;
    }
};

class RobotMgr
{
public:
    RobotMgr(/* args */){}
    ~RobotMgr(){}
    int run(istream& input,ostream& output, int cmdCountOnce){
        vector<string> vLines;
        string line;
        Robot rbt(5);
        Report reportObj;
        rbt.SetReportFunc(bind(&Report::reportResult,&reportObj,placeholders::_1));
        int framecount = cmdCountOnce;
        int iCount =0;
        int index =0;

        while(true){
            while(index < framecount && getline(input,line)){
                for_each(line.begin(),line.end(),::toupper);//upper.
                vLines.push_back(line);
                ++index;
            }

            //run robot
            iCount += index;
            if( rbt.runCommand(vLines) < 0){
                cerr << "Robot run command error! \nGoodBye!" << endl;
                return -1;
            }
            if(index < framecount){//file read finished.
                cout << "Finshed all command (count:" << iCount <<"). GoodBye!" << endl;
            return 0;
            } 
            index =0;vLines.clear();
        }
        return 0;
    }
};
