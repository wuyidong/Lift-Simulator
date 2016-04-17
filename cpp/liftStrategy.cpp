#include "lift.h"

using namespace std;

// the lift is stop, 0x0
void Lift::liftStrategy0()
{
	if ( requestList.getPassengerNum(currFloor) > 0)
	{
		setStateRun();
		setStateOpen();
		boardPassengers();
		openTimeMinus();
	}
	int upperFloor = requestList.nextRequestUpperThan(currFloor);
	int lowerFloor = requestList.nextRequestLowerThan(currFloor);
	if (upperFloor != -1 && lowerFloor != -1)
		direction = upperFloor - currFloor > currFloor - lowerFloor ? DOWN : UP;
	else if (upperFloor != -1)
		direction = UP;
	else if (lowerFloor != -1)
		direction = DOWN;
	else
		return;	// keep stop
	setStateRun();
	currFloor = direction == UP ? currFloor + 1 : currFloor - 1;
}

// the lift is run but not open door, 0x20
void Lift::liftStrategy1()
{
	if (desFloorList[currFloor].empty() && requestList.getPassengerNum(currFloor) <= 0)
	{
		if (count == 0)
		{
			if (direction == UP && requestList.nextRequestUpperThan(currFloor) > 0)
				currFloor++;	// keep up
			else if (direction == DOWN && requestList.nextRequestLowerThan(currFloor) > 0)
				currFloor--;	// keep down
			else
				setStateStop();	//stop
		}
		else
			currFloor = direction == UP ? currFloor + 1 : currFloor - 1;	// keep origin direction
	}
	else
	{
		setStateOpen();
		getoffPassengers();
		// board passengers
		boardPassengers();
		openTimeMinus();
	}
}

// the lift is run and open, the open time just exhaust, 0x30
void Lift::liftStrategy2()
{
	setStateClose();
	if (count == 0)
	{
		setStateStop();
		return;
	}
	direction = countUpPassengers() > countDownPassengers() ? UP : DOWN;
	currFloor = direction == UP ? currFloor + 1 : currFloor - 1;
}

// the lift is run and open, waiting, > 0x30
void Lift::liftStrategy3()
{
	boardPassengers();
	openTimeMinus();
}