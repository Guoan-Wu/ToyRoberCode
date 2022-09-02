#include "robot.h"
#include <cassert>
#include "myString.h"

 ParseCommand::ParseCommand(){
 }

 ParseCommand::~ParseCommand(){
 }

/*
Extract parameters from a command. 
E.g., "PLACE 3,3,NORTH"->RobotCmd(CMD_PLACE,3,3,NORTH).
return: cmdReturn with parameters. But CMD_UNKNOWN will be set in cmdReturn.cmd if there are errors.
*/
RobotCmd ParseCommand::parseACommand(const string& cmd) {
    RobotCmd cmdReturn;
    vector<string> cmdSplited = MyString::split(cmd," ");
    if(cmdSplited.size() ==0)
        return cmdReturn;
    string sCmdType = cmdSplited.at(0);
    //change the type to cmdtype 
    vector<unsigned int> cmdParams;
    vector<string> params;
    auto iterType = find(m_vCmdType.cbegin(),m_vCmdType.cend(),sCmdType);
    if(iterType == m_vCmdType.cend()) return cmdReturn;
    CmdType cmdType = static_cast<CmdType>(iterType - m_vCmdType.cbegin());

    switch(cmdType){
        case CMD_PLACE:{//PLACE:get x,y,f
            Direction f;
            if(cmdSplited.size() <2) return cmdReturn;

            params = MyString::split(cmdSplited.at(1),",");
            if(params.size() == 3){
                
                if(!MyString::isNumber(params.at(0)) ||
                    !MyString::isNumber(params.at(1)) )
                    return cmdReturn;
                
                auto iterF = find(cmdDirections.cbegin(),cmdDirections.cend(),params.at(2));
                if(iterF != cmdDirections.cend()){
                    f = static_cast<Direction>(iterF-cmdDirections.cbegin());
                } else return cmdReturn;
            } else return cmdReturn;
            //Ok. set value.
            cmdReturn.cmd = CMD_PLACE;
            cmdReturn.x = stoi(params.at(0).c_str());
            cmdReturn.y = stoi(params.at(1).c_str());
            cmdReturn.f = f;
            break;
        }
        default://Not PLACE, no args.
            cmdReturn.cmd = cmdType;
            break;
    }
    return cmdReturn;
}


Robot::Robot(unsigned int uiTableLength)
{
    m_tableSquare.setrange(uiTableLength);
}

Robot::~Robot()
{
}

 int Robot::runCommand(vector<string>& cmds){
        
        //upper and remove extra blank spaces. do later.

        ParseCommand parse;
        RobotCmd oneCmd;
        bool error = false;
        //1. find "PLACE" if !m_bPlaced
        auto iter = cmds.cbegin();
        while(!m_bPlaced && iter != cmds.cend() && !error){
            oneCmd = parse.parseACommand(*iter);
            if(oneCmd.cmd == CMD_PLACE){
                if(place(oneCmd) >= 0) m_bPlaced = true;
            }
            ++iter;
            if(oneCmd.cmd == CMD_UNKNOWN)
                error = true;
                return -1;
        }

        //do cmd one by one.
        for(;iter != cmds.cend();++iter){
            oneCmd = parse.parseACommand(*iter);
            switch (oneCmd.cmd)
            {
            case CMD_MOVE:
                move();
                break;
            case CMD_LEFT:
                left();
                break;
            case CMD_RIGHT:
                left();
                break;
            case CMD_REPORT:
                report();
                break;
            case CMD_PLACE:
                place();
                break;
            default:
                return -1;
                break;
            } 
        }

        return 0;
        
    }
void Robot::clearPlacedState(){
    m_bPlaced = false;
}

int Robot::place(const RobotCmd& cmd){
    if(m_tableSquare.inside(cmd.x,cmd.y) <0) return -1;
    m_lastState = cmd;
    return 0;
}
int Robot::move(){
    auto result = m_tableSquare.canMove(m_lastState);
    if(!result.first)
        return -1;
    m_lastState = result.second;
    return 0;
}
int Robot::left(){return 0;}
int Robot::right(){return 0;}
int Robot::report(){return 0;};

   