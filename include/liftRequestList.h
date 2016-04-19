#ifndef LIFTREQUESTLIST_H
#define LIFTREQUESTLIST_H

#include <vector>
#include <queue>
#include "passenger.h"

class LiftRequestList {
public:
	LiftRequestList(int maxFloor);

	int nextRequestUpperThan(int floor);
	int nextRequestLowerThan(int floor);
	int getPassengerNum(int floor);	// num of passengers at floor
	bool haveRequest(int floor);
	void newRequest(Passenger* p);
	Passenger* boardPassenger(int floor);
private:
	int maxFloor;
	std::vector<std::queue<Passenger*>> requests;
};

#endif
