#include "lift.h"
#include "passenger.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

// default lift configuration
int Lift::maxFloor = 9;
int Lift::capacity = 12;
int Lift::speed = 1;
int Lift::totalOpenTime = 6;

int Lift::liftCount = 3;
vector<Lift*> Lift::lifts(liftCount);

int Lift::timeTick = 0;
LiftRequestList Lift::requestList(maxFloor);

long long Lift::passengerCount = 0;
long long Lift::waitTimeCount = 0;
long long Lift::transitTimeCount = 0;

void Lift::setMaxFloor(int maxFloor)
{
	Lift::maxFloor = maxFloor;
	requestList = LiftRequestList(maxFloor);
}

int Lift::getMaxFloor()
{
	return maxFloor;
}

void Lift::setCapacity(int cap)
{
	Lift::capacity = cap;
}

void Lift::setSpeed(int speed)
{
	Lift::speed = speed;
}

void Lift::setOpenTime(int totalOpenTime)
{
	Lift::totalOpenTime = totalOpenTime;
}

void Lift::setLiftCount(int num)
{
	liftCount = num;
	lifts = vector<Lift*>(liftCount);
}

void Lift::init()
{
	for (int i = 0; i < liftCount; i++)
	{
		lifts[i] = new Lift();
	}
}

bool Lift::parseIni(IniField* fields, int count)
{
	fstream fs;
	fs.open(INI_FILE_PATH, ios_base::in);
	if (!fs.is_open())
	{
		return false;
	}

	return true;
}

void Lift::close()
{
	for (int i = 0; i < liftCount; i++)
	{
		delete lifts[i];
	}
}

Lift::Lift() : desFloorList(maxFloor + 1)
{
	count = 0;
	direction = UP;
	currFloor = 0;
	state = 0x0;	// stop, close door
}

void Lift::newRequest(Passenger* p)
{
	p.setStartTime(timeTick);	// time arriving at the floor
	requestList.newRequest(p);
}

void Lift::runOneTimeTick()
{
	//for (int i = 0; i <= maxFloor; i++)
	//	cout << requestList.getPassengerNum(i) << "  ";
	//cout << endl;
	for (int i = 0; i < liftCount; i++)
	{
		lifts[i]->runOneTimeTick_lift();
		//cout << '|' << lifts[i]->currFloor << "  " << lifts[i]->count << "  " << lifts[i]->direction << "  ";
	}
	//cout << endl << endl;
	timeTick++;
}

// the simple lift control logic
void Lift::runOneTimeTick_lift()
{
	if (currFloor > maxFloor)
	{
		cout << "exceed max floor!" << endl;
		close();
		exit(0);
	}
	switch (state) {
	case 0x0:
		liftStrategy0();
		break;
	case 0x20:
		liftStrategy1();
		break;
	case 0x30:
		liftStrategy2();
		break;
	default:
		liftStrategy3();
		break;
	}
}

void Lift::boardPassengers()
{
	int num = min(capacity - count, requestList.getPassengerNum(currFloor));
	for (int i = 0; i < num; i++)
	{
		Passenger* p = requestList.boardPassenger(currFloor);
		p->setBoardTime(timeTick);	// time boarding on a floor
		desFloorList[p->getDesFloor()].push_back(p);
		count++;
	}
}

void Lift::getoffPassengers()
{
	// get off passengers
	count -= desFloorList[currFloor].size();
	for (int i = 0; i < desFloorList[currFloor].size(); i++)
	{
		Passenger* p = desFloorList[currFloor][i];
		p->setGetoffTime(timeTick);
		waitTimeCount += p->getBoardTime() - p->getStartTime();
		transitTimeCount += p->getGetoffTime() - p->getBoardTime();
		passengerCount++;
	}
	desFloorList[currFloor].clear();
}

int Lift::countUpPassengers()
{
	int cnt = 0;
	for (int i = currFloor + 1; i <= maxFloor; i++)
		cnt += desFloorList[i].size();
	return cnt;
}

int Lift::countDownPassengers()
{
	int cnt = 0;
	for (int i = 0; i < currFloor; i++)
		cnt += desFloorList[i].size();
	return cnt;
}
