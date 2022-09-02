
#include "myString.h"
#include "robot.h"
#include <cassert>

 //unit test for robert.h. Using googletese would be better. 

//base calss for test, defining an interface "test_all" that is used to 
//implement all unit tests for a class. 
 class test_base
 {
 public:
    test_base(/* args */){}
    ~test_base(){}
    virtual void test_all()=0;
 };
 
 
 //unit test for class ParseCommand.
class test_ParseCommand:public test_base {
public:
    test_ParseCommand(){}
    ~test_ParseCommand(){}
    virtual void test_all(){
        test_all_parseACommand();
    }
    void test_all_parseACommand(){
        //{valid
            //PLACE cmd.
        test_parseACommand("PLACE 3,3,NORTH",RobotCmd(CMD_PLACE,3,3,NORTH));
        test_parseACommand("PLACE 10,10,SOUTH",RobotCmd(CMD_PLACE,10,10,SOUTH));
        test_parseACommand("PLACE 21,56999,EAST",RobotCmd(CMD_PLACE,21,56999,EAST));
        test_parseACommand("PLACE 999999999,888888888,WEST",
                        RobotCmd(CMD_PLACE,999999999,888888888,WEST));
            //other cmd types.
        test_parseACommand("MOVE",RobotCmd(CMD_MOVE,0,0,NORTH));
        test_parseACommand("LEFT",RobotCmd(CMD_LEFT,0,0,NORTH));
        test_parseACommand("RIGHT",RobotCmd(CMD_RIGHT,0,0,NORTH));
        test_parseACommand("REPORT",RobotCmd(CMD_REPORT,0,0,NORTH));

        //}
        //{invalid.
            //float value.
        test_parseACommand("PLACE 2,2.5,WEST",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //wrong direction
        test_parseACommand("PLACE 2,3,zero",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //x or y are not digital.
        test_parseACommand("PLACE 2,y,WEST",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
        test_parseACommand("PLACE x,3,SOUTH",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //x or y are negative.
        test_parseACommand("PLACE 2,-10,EAST",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
        test_parseACommand("PLACE -62,80,EAST",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //cmd type is not at zero position.
        test_parseACommand(" PLACE 3,3,EAST",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //blank input.
        test_parseACommand("",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //wrong cmd type.
        test_parseACommand("Place 3,3,NORTH",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
        test_parseACommand("HELLO 3,3,NORTH",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //lacking args in PLACE cmd.
        test_parseACommand("PLACE",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
        test_parseACommand("PLACE 2,NORTH",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //too many args in PLACE cmd.
        test_parseACommand("PLACE 2,3,5,NORTH",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
        //}
    }
    void test_parseACommand(const string& cmd,const RobotCmd& answer){
        ParseCommand obj;
        RobotCmd result = obj.parseACommand(cmd);
        assert(result == answer);
    }
   
};
 //unit test for class MyString.
class test_mystring
{
private:
    /* data */
public:
    test_mystring(/* args */){}
    ~test_mystring(){}
    virtual void test_all(){
        test_all_split();
    }
     void test_all_split(){
        //invalide parameters.
        test_split("LEFT","",{});
        test_split("",",",{});
        //can't split.
        test_split("REPORT","break",{"REPORT"});
        test_split("RIGHT",",",{"RIGHT"});
        test_split("PLACE1,2,NORTH"," ",{"PLACE1,2,NORTH"});
        //normal situation.
        test_split("PLACE 1,2,NORTH"," ",{"PLACE","1,2,NORTH"});
        test_split("4,7,EAST",",",{"4","7","EAST"});
        test_split("MOVE"," ",{"MOVE"});
    }
private:
    void test_split(const string cmd,const string delimiter,vector<string> answer){
        MyString obj;
        vector<string> result = obj.split(cmd,delimiter);
        assert(result == answer);
    }
};


// int main(){
//     test_mystring   objMyString;
//     objMyString.test_all();

//     test_ParseCommand obj;
//     obj.test_all();
//     return 0;
// }