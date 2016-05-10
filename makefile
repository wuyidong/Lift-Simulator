LiftSimulator:main.cpp liftRequestList.o liftStrategy.o lift.o parseIni.o
	g++ -g -o LiftSimulator main.cpp liftRequestList.o liftStrategy.o lift.o parseIni.o -I./include

liftRequestList.o:./cpp/liftRequestList.cpp
	g++ -g -c -o liftRequestList.o ./cpp/liftRequestList.cpp -I./include

liftStrategy.o:./cpp/liftStrategy.cpp
	g++ -g -c -o liftStrategy.o ./cpp/liftStrategy.cpp -I./include

lift.o:./cpp/lift.cpp
	g++ -g -c -o lift.o ./cpp/lift.cpp -I./include

parseIni.o:./cpp/parseIni.cpp
	g++ -g -c -o parseIni.o ./cpp/parseIni.cpp -I./include

.PHONY:clean
clean:
	rm *.o LiftSimulator
