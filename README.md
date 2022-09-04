# The Toy Robot Coding Challenge
A console application running a toy robot inputted by users. 
# Requirement Description
This project simulates a toy robot that moves on a square table top with dimensions 5 x 5 units. There are no obstructions on the table. In other words, the robot can move on the table surface smoothly. The application moves the robot in the table surface by receipting commands that users input in a file or type in a terminal. The commands to run the robot are as follows:
1. PLACE X,Y,F
2. MOVE
3. LEFT
4. RIGHT
5. REPORT
   
PLACE will put the toy robot on the table in position X,Y and facing NORTH, SOUTH, EAST or WEST. The origin (0,0) can be considered to be the SOUTH WEST most corner. It is required that the first command to the robot is a PLACE command, after that, any sequence of commands may be issued, in any order, including another PLACE command. 
MOVE will move the toy robot one unit forward in the direction it is currently facing.
LEFT and RIGHT will rotate the robot 90 degrees in the specified direction without changing the position of the robot.
REPORT will announce the X,Y and F of the robot, which displays on the terminal. 
The application runs the commands according to the following rules:
1. The console application must prevent the robot from being outside of the table square.
2. All commands will be ignored until a "PLACE" command with position inside the table square is run.
3. A command cannot be run if it will cause the robot being outside of the table square, but commands after that will be processed.

# Getting started
## Dependencies
1. Ubuntu 5.15.0-46-generic
2. g++ 9.4.9
3. C++17

## Installing
1. Downloading the repository to a path and unzipping it. All files of the project will be in the 'ToyRoberCode' path. 
2. Run "make" in the 'ToyRoberCode' path.
3. 'robotMain' and 'test_robot' will be created in the path. The former is the main execute file, and the latter is the testing application for the project.

## Executing programmes
This section includes executing description for main application and testing application. 
### Main execute file
Running ```./robotMain -h``` will display help information as follows:
```
robotMain [-i <filename>]
Examples:
robotMain //input is cin.
robotMain -i ./cmd1.txt //input file name is ./cmd1.txt that includes commands to run the robot.
robotMain ./cmd1.txt //same to the above. 
```
The first row command in the examples above means the input of the application is users' typing on the terminal. That is to say, the application will run the inputting commands one by one. 
The second and third row commands are the same, which provides all commands in a file. The application will run all the commands in the file. 
The application reacts will users by outputting results on a terminal. 
Some typing errors will be automatic processed by the application, such as lower command, additional blank spaces. But if users type wrong commands, the application will ignore these commands and keep in running. 
### Testing application
Running ```./test_robot``` will display a series of testing results on a terminal. The testing is successful if '[Robot::runCommand() OK]' is on the bottom of the outputs. Otherwise, information like 'Aborted (core dumped)' will be displayed on the bottom of the terminal.

# design descrption
## class description
This section describe main classes in the project,including main programme and testing classes. The robotMain application includes the following classes:
* MyString: processing concerned to string, including split() and IsNumber().
ParseCommand: Parsing inputting commands and converting to inner command formats.
* Robot: simulating the toy robot's behavior.
* RobotMgr: receiving the inputs for the robot and running the robot to move in the 'robotMain' application.
* Main() in robotMain.cpp: dealing with inputting args, reading a command file and running the whole application.

Besides, the following classes are in the testing application.
* Test_base: An interface for  testing classes in the project.
* Test_mystring: unit tests for MyString class.
* Test_ParseCommand:  unit tests for ParseCommand class.
* Test_robot:  unit tests for Robot class.

## Design highlights
* Three layers, including parsing commands, simulating robot's behavior, and outputting results. The structure would be helpful to optimise. E.g., multiple users can input commands from the Internet to move a robot.
* Using a functional object interface to output results, which provide flexibility to develop various types of outputting.
* A pure virtual class Test_base is designed as an interface for testing classes. The interface provides two benefits: 
    1. The Factory Pattern is adopted to create pointers for testing classes without exposing the classes' details.
    2. The virtual function test_all() provide a standard function to all derived class.
