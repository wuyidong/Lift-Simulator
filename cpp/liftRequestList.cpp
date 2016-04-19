#include "../include/liftRequestList.h"
#include "passenger.h"

LiftRequestList::LiftRequestList(int maxFloor) : maxFloor(maxFloor), requests(maxFloor + 1)
{
}

int LiftRequestList::nextRequestUpperThan(int floor)
{
	for (int i = floor + 1; i <= maxFloor; i++)
	{
		if (requests[i].size() > 0)
			return i;
	}
	return -1;
}

int LiftRequestList::nextRequestLowerThan(int floor)
{
	for (int i = floor - 1; i >= 0; i--)
	{
		if (requests[i].size() > 0)
			return i;
	}
	return -1;
}

int LiftRequestList::getPassengerNum(int floor)
{
	return (floor >= 0 && floor <= maxFloor) ? requests[floor].size() : -1;
}

bool LiftRequestList::haveRequest(int floor)
{
	if (floor < 0 || floor > maxFloor)
		return false;
	return requests[floor].empty();
}

void LiftRequestList::newRequest(Passenger* p)
{
	requests[p->getStartFloor()].push(p);
}

Passenger* LiftRequestList::boardPassenger(int floor)
{
	//if (floor < 0 || floor > maxFloor)
	//	return;
	Passenger* p = requests[floor].front();
	requests[floor].pop();
	return p;
}
