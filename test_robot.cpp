
#include "myString.h"
#include "robot.h"
#include <cassert>
#include <array>
#include <memory>
 //unit test for robert.h. Using googletese would be better. 

//base calss for test, defining an interface "Test_all" that is used to 
//implement all unit tests for a class. 
 class Test_base
 {
 public:
    Test_base(/* args */){}
    ~Test_base(){}
    virtual void test_all()=0;
    void printStartTip(string sFuncName){
        cout << "[Test " << sFuncName << " ...]" <<endl;
    }
    void printEndTip(string sFuncName){
        cout << "[" << sFuncName << " OK]" <<endl;
    }
 };
 
 
 //unit test for class ParseCommand.
class Test_ParseCommand:public Test_base {
public:
    Test_ParseCommand(){}
    ~Test_ParseCommand() {}
    void test_all() override {
        printStartTip("ParseCommand::parseACommand()");
        test_all_parseACommand();
        printEndTip("ParseCommand::parseACommand()");
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

            //extra blank spaces.
        test_parseACommand(" PLACE  6,3,NORTH",RobotCmd(CMD_PLACE,6,3,NORTH));            
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
        test_parseACommand("3,3,EAST PLACE",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //blank input.
        test_parseACommand("",RobotCmd(CMD_UNKNOWN,0,0,NORTH));
            //wrong cmd type.
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
class Test_mystring : public Test_base
{
private:
    /* data */
public:
    Test_mystring(/* args */){}
    ~Test_mystring(){}
    void test_all() override {
        printStartTip("MyString::split()");
        test_all_split();
        printEndTip("MyString::split()");
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

 //unit test for class robot.
class Test_robot : public Test_base
{
private:
    /* data */
public:
    Test_robot(/* args */){}
    ~Test_robot(){}
    void test_all() override {
        printStartTip("Robot::place()");
        test_place();
        printEndTip("Robot::place()");

        printStartTip("Robot::move()");
        test_move();
        printEndTip("Robot::move()");

        printStartTip("Robot::left()");
        test_left();
        printEndTip("Robot::left()");

        printStartTip("Robot::right()");
        test_right();
        printEndTip("Robot::right()");

        printStartTip("Robot::report()");
        test_report();
        printEndTip("Robot::report()");

        printStartTip("Robot::runCommand()");
        test_runCommand();
        printEndTip("Robot::runCommand()");
    }
    void test_place(){
        Robot obj(5);
        RobotCmd cmd={CMD_PLACE,0,0,NORTH};
        int result;
        
        //{invalid
            //wrong cmd.
        result = obj.place({CMD_MOVE,0,0,NORTH}); assert(result == -1);
            //out of table square
        result = obj.place({CMD_PLACE,0,5,EAST}); assert(result == -1);
        result = obj.place({CMD_PLACE,5,0,NORTH}); assert(result == -1);
        result = obj.place({CMD_PLACE,6,3,EAST}); assert(result == -1);
        //}

        //{valid
        auto func = [&obj](const RobotCmd& cmd) ->bool {
            int result = obj.place(cmd);
            return (result == 0 && obj.m_bPlaced && obj.m_lastState == cmd );
        };
        assert(func({CMD_PLACE,0,0,NORTH}));
        assert(func({CMD_PLACE,4,0,SOUTH}));
        assert(func({CMD_PLACE,0,4,EAST}));
        assert(func({CMD_PLACE,3,2,EAST}));
        //}
    }
    void test_move(){
        Robot obj(5);

        //{invalid
        auto func1 = [&obj](const RobotCmd& ori, const RobotCmd& newValue) -> bool {
            obj.place(ori);
            int result = obj.move(); 
            return result <0 && obj.m_lastState == ori;
        };
        assert(func1({CMD_PLACE,0,4,NORTH},{CMD_PLACE,0,4,NORTH}));
        assert(func1({CMD_PLACE,0,0,SOUTH},{CMD_PLACE,0,0,SOUTH}));
        assert(func1({CMD_PLACE,4,1,EAST},{CMD_PLACE,4,1,EAST}));
        assert(func1({CMD_PLACE,0,2,WEST},{CMD_PLACE,0,2,WEST}));
        //}

        //{valid
        auto func2 = [&obj](const RobotCmd& ori, const RobotCmd& newValue) -> bool {
            obj.place(ori);
            int result = obj.move(); 
            return result >=0 && obj.m_lastState == newValue;
        };
        assert(func2({CMD_PLACE,0,0,NORTH},{CMD_PLACE,0,1,NORTH}));
        assert(func2({CMD_PLACE,0,3,NORTH},{CMD_PLACE,0,4,NORTH}));
        assert(func2({CMD_PLACE,0,1,SOUTH},{CMD_PLACE,0,0,SOUTH}));
        assert(func2({CMD_PLACE,0,4,SOUTH},{CMD_PLACE,0,3,SOUTH}));
        assert(func2({CMD_PLACE,0,0,EAST},{CMD_PLACE,1,0,EAST}));
        assert(func2({CMD_PLACE,3,2,EAST},{CMD_PLACE,4,2,EAST}));
        assert(func2({CMD_PLACE,1,0,WEST},{CMD_PLACE,0,0,WEST}));
        assert(func2({CMD_PLACE,4,1,WEST},{CMD_PLACE,3,1,WEST}));
        //}
    }
    void test_left(){
        Robot obj(5);
        //{valid
        auto func = [&obj](const RobotCmd& ori, const RobotCmd& newValue) -> bool {
            obj.place(ori);
            int result = obj.left(); 
            return result >=0 && obj.m_lastState == newValue;
        };
        assert(func({CMD_PLACE,0,0,NORTH},{CMD_PLACE,0,0,WEST}));
        assert(func({CMD_PLACE,0,1,SOUTH},{CMD_PLACE,0,1,EAST}));
        assert(func({CMD_PLACE,3,2,EAST},{CMD_PLACE,3,2,NORTH}));
        assert(func({CMD_PLACE,4,1,WEST},{CMD_PLACE,4,1,SOUTH}));
        //}
    }
    void test_right(){
        Robot obj(5);
        //{valid
        auto func = [&obj](const RobotCmd& ori, const RobotCmd& newValue) -> bool {
            obj.place(ori);
            int result = obj.right(); 
            return result >=0 && obj.m_lastState == newValue;
        };
        assert(func({CMD_PLACE,0,0,NORTH},{CMD_PLACE,0,0,EAST}));
        assert(func({CMD_PLACE,0,1,SOUTH},{CMD_PLACE,0,1,WEST}));
        assert(func({CMD_PLACE,3,2,EAST},{CMD_PLACE,3,2,SOUTH}));
        assert(func({CMD_PLACE,4,1,WEST},{CMD_PLACE,4,1,NORTH}));
        //}
    }
    void test_report(){
        Robot obj(5);
        obj.place({CMD_PLACE,4,1,WEST});

        //invalid 
        assert(obj.report() < 0);
        //valid
        auto func = [](const RobotCmd & cmd){
            cout << "Output robot's position: " << cmd << endl;  };
        obj.SetReportFunc(func);
        assert(obj.report() >=0); 
    }
    void test_runCommand(){
        Robot obj(5);
        vector<RobotCmd> vReport;
        auto funcReport = [&vReport](const RobotCmd &cmd){
            cout << "Output robot's position" <<  cmd << endl;  
            vReport.push_back(cmd);
            };
        obj.SetReportFunc(funcReport);
       
        //{invalid
         auto funcInvalid = [&obj,&vReport](const vector<string> &cmds,
        const vector<RobotCmd>& report) -> bool {
            vReport.clear();
            obj.clearPlacedState();
            int result =obj.runCommand(cmds);
            return result <0 && vReport == report;
        };
            //wrong cmd, stop.
        assert(funcInvalid({"PLACE 2,3,EAST","MOVE","MOVE","LEFT","REPORT","MOVE",
                "REPORT","RIGHT","MOVE","MOVE","MOVE","REPORT","DOWN","LEFT","REPORT"},
                {{CMD_PLACE,4,3,NORTH},{CMD_PLACE,4,4,NORTH},{CMD_PLACE,4,4,EAST}}));
        //}

        //{valid
         auto funcValidate = [&obj,&vReport](const vector<string> &cmds,
        const vector<RobotCmd>& report) -> bool {
            vReport.clear();
            obj.clearPlacedState();
            int result =obj.runCommand(cmds);
            return result >=0 && vReport == report;
        };
            // no 'PLACE', no action.
        assert(funcValidate({"MOVE","LEFT","REPORT","MOVE","REPORT","RIGHT","MOVE",
                "MOVE","LEFT","MOVE","RIGHT","REPORT"},{}));
            //ignore cmd before the first 'PLACE'
        assert(funcValidate({"MOVE","RIGHT","REPORT","PLACE 2,2,WEST","LEFT","RIGHT",
                "LEFT","MOVE","MOVE","MOVE","RIGHT","REPORT"},
                {{CMD_PLACE,2,0,WEST}}));
            //Ignore "MOVE" causing falling, but continue to do coming command.
        assert(funcValidate({"PLACE 3,2,SOUTH","MOVE","MOVE","MOVE",
                "LEFT","MOVE","REPORT"},{{CMD_PLACE,4,0,EAST}}));    
            //normal.
        assert(funcValidate({"PLACE 0,0,NORTH","LEFT","RIGHT","MOVE","MOVE","MOVE","MOVE",
                "LEFT","MOVE","RIGHT","REPORT"},{{CMD_PLACE,0,4,NORTH}}));
         //report many times.
        assert(funcValidate({"PLACE 1,2,EAST", "LEFT","REPORT","RIGHT","LEFT","MOVE",
                "MOVE","MOVE","RIGHT","REPORT","MOVE","LEFT"},
                {{CMD_PLACE,1,2,NORTH},{CMD_PLACE,1,4,EAST}}));
         //}
    }
};

//Using factory pattern to hide certain classes's details.
//only expose base class that is an interface.
unique_ptr<Test_base> createObject(string name){
    if (name =="mystring") return make_unique<Test_mystring>();
    else if (name =="parsecommand") return make_unique<Test_ParseCommand>();
    else if (name =="robot") return make_unique<Test_robot>();
    return nullptr;
}
void testClass(string name){
    unique_ptr<Test_base> pObj = createObject(name);
    assert(pObj != nullptr);
    pObj->test_all();
}
int main(){
    testClass("mystring");
    testClass("parsecommand");
    testClass("robot");
    return 0;
}