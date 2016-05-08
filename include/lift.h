#ifndef LIFT_H
#define LIFT_H

#include "liftRequestList.h"
#include "passenger.h"
#include <vector>
#include <string>
#include <map>

#define INI_FIELD_COUNT 6
#define INI_FILE_PATH "./config.ini"

struct IniField;

enum Direction { UP, DOWN };

class Lift {
public:
	Lift();

	static void init(); 
	static bool parseIni(std::map<std::string, IniField>& paras);
	static void close();
	static void runOneTimeTick();
	static void newRequest(Passenger* p);

	static void setMaxFloor(int maxFloor);
	static int getMaxFloor();
	static void setCapacity(int cap);
	static void setSpeed(int speed);
	static void setOpenTime(int openTime);
	static void setLiftCount(int num);

	static double getAverageWaitTime() {
		return (double)waitTimeCount / passengerCount;
	}
	static double getAverageTransitTime() {
		return (double)transitTimeCount / passengerCount;
	}
	static double getAverageTime() {
		return (double)(waitTimeCount + transitTimeCount) / passengerCount;
	}
	static long long getPassengerCount() {
		return passengerCount;
	}
private:
	void runOneTimeTick_lift();
	void boardPassengers();		// board sa many as passengers at current floor
	void getoffPassengers();	// get off all passengers which destination is currFloor
	int countUpPassengers();	// num of passengers which destination is upper
	int countDownPassengers();	// num of passengers which destination is lower
	inline void setStateRun() {
		state = 0x20;
	}
	inline void setStateStop() {
		state = 0x0;
	}
	inline void setStateOpen() {
		state = 0x30;
		state += totalOpenTime;
	}
	inline void setStateClose() {
		state = 0x20;
	}
	// minus the open time one time tick
	inline void openTimeMinus()	{
		if (state & 0xF)
			state--;
	}

private:
	// these are lift strategies in different situation
	void liftStrategy0();
	void liftStrategy1();
	void liftStrategy2();
	void liftStrategy3();

private:
	int count;	// current number of persons in the lift
	Direction direction;
	int currFloor;
	char state;
	std::vector<std::vector<Passenger*> > desFloorList;

private:
	static int maxFloor;
	static int capacity;
	static int loadCapacity;
	static int speed;			// use TimeTicks pre Floor as unit
	static int totalOpenTime;	// use TimeTicks as unit

	static int liftCount;
	static std::vector<Lift*> lifts;

	static int timeTick;
	static LiftRequestList requestList;

	static long long passengerCount;
	static long long waitTimeCount;
	static long long transitTimeCount;
};

enum IniFieldType { INT, STRING };

struct IniField {
	IniField(std::string name, IniFieldType type, void* addr)
	{
		this->name = name;
		this->type = type;
		this->addr = addr;
	}

	std::string name;
	IniFieldType type;
	void* addr;
};

#endif
