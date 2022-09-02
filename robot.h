#pragma once
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include "robot.h"
#include<map>
using namespace std;
#define PLACE "PLACE"
#define MOVE "MOVE"
#define LEFT "LEFT"
#define RIGHT "RIGHT"
#define REPORT "REPORT"
enum CmdType{
    CMD_PLACE,
    CMD_MOVE,
    CMD_LEFT,
    CMD_RIGHT,
    CMD_REPORT,
    CMD_UNKNOWN
};
enum Direction{
    NORTH,
    SOUTH,
    EAST,
    WEST
};
//The origin (0,0) is the SOUTH WEST most corner.
_Undefined_class TableSquare{
    TableSquare(){}
    ~TableSquare(){};
void setrange(unsigned int length){
    m_length = length;
}
bool inside(unsigned int x, unsigned int y){
    if (x >= m_length || y >= m_length)
        return false;
    return true;
}
pair<bool,RobotCmd> canMove(RobotCmd& currentPos){
    RobotCmd newPos = currentPos;
    auto offset = m_mapDirePoint[currentPos.f];
    unsigned int x,y;
    x = currentPos.x + offset.first;
    y = currentPos.y + offset.second;
    if(x >= m_length || y >= m_length) return {false,newPos};
    newPos.x = x;
    newPos.y = y;
    return {true,newPos};
}
private:
    unsigned int m_length;
    map<Direction,pair<int,int>> m_mapDirePoint{{NORTH,{0,1}},{SOUTH,{0,-1}},
                            {EAST,{1,0}},{WEST,{-1,0}}};
};



struct RobotCmd{
    RobotCmd(){}
    RobotCmd(CmdType cmd,unsigned int x, unsigned int y, Direction f):
        cmd(cmd),x(x),y(y),f(f){}
    RobotCmd(const RobotCmd& l):cmd(l.cmd),x(l.x),y(l.y),f(l.f){}
    inline bool operator==(const RobotCmd& l) {
        return (l.cmd==cmd) && (l.x ==x) && (l.y ==y) && (l.f ==f);
    }
    CmdType cmd{CMD_UNKNOWN};
    unsigned int x{0};
    unsigned int y{0};
    Direction f{NORTH};
};


class ParseCommand{
public:
   ParseCommand();
   ~ParseCommand();
    RobotCmd parseACommand(const string& cmd);
private:
    vector<string> cmdDirections{"NORTH","SOUTH","EAST","WEST"};
    //the following items must keep the same order with CmdType.
    vector<string> m_vCmdType{PLACE,MOVE,LEFT,RIGHT,REPORT};
    

};
/*
input: commands (text formation) in a container or one by one
output: report result via a function object.*/
class Robot
{

public:
    Robot(unsigned int uiTableLength);
    virtual ~Robot();
    int runCommand(vector<string>& cmds);
    inline void clearPlacedState();
    int place(const RobotCmd& cmd);
    int move();
    int left();
    int right();
    int report();

private:
    /* data */
    bool m_bPlaced{false};
    RobotCmd    m_lastState;
    TableSquare m_tableSquare;
};

