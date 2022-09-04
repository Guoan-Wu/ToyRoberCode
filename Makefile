CC = g++
C_FLAGS = -std=c++17

exeObjs = robotMain test_robot
all : $(exeObjs)

testObjs = robot.o test_robot.o
test_robot : $(testObjs)
	$(CC) -o test_robot $(testObjs)

test_robot.o : test_robot.cpp myString.h robot.h
	$(CC) $(C_FLAGS) -c test_robot.cpp

mainObjs = robot.o robotMain.o
robotMain : $(mainObjs)
	$(CC) -o robotMain $(mainObjs)

robotMain.o : robotMain.cpp robotMgr.h
	$(CC) $(C_FLAGS) -c robotMain.cpp

robot.o : robot.cpp robot.h myString.h
	$(CC) $(C_FLAGS) -c robot.cpp

clean:
	rm *.o