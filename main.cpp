#include <iostream>
#include <cstdlib>
#include <ctime>
#include "lift.h"
#include "passenger.h"

using namespace std;

long long testPassengerCount = 0;
long long testTransitTimeCount = 0;

Passenger generatePassenger(int maxFloor)
{
	int desFloor = rand() % (maxFloor + 1);
	int startFloor = rand() % (maxFloor + 1);
	float weight = (float) rand() / RAND_MAX * PASSENGER_MAX_WEIGHT; 
	Passenger p(weight, startFloor, desFloor);
	//p.desFloor = 8;
	//p.startFloor = 0;
	return p;
}

void generatePassengers(int timeTick)
{
	int countPassengers = 1;	// need exponential distribution here
	srand(time(NULL));
	while (countPassengers > 0)
	{
		Passenger p = generatePassenger(Lift::getMaxFloor());
		if (p.getDesFloor() == p.getStartFloor()) 
			continue;
		testPassengerCount++;
		testTransitTimeCount += p.getStartFloor() > p.getDesFloor() ? p.getStartFloor() - p.getDesFloor() : p.getDesFloor() - p.getStartFloor();
		Lift::newRequest(p);
		countPassengers--;
	}
}

int main(void)
{
	int totalTime = 7200, maxFloor = 9, speed = 1, capacity = 12, totalOpenTime = 6;
	int liftCount = 3;


	Lift::setCapacity(capacity);
	Lift::setMaxFloor(maxFloor);
	Lift::setOpenTime(totalOpenTime);
	Lift::setSpeed(speed);
	Lift::setLiftCount(liftCount);

	Lift::init();

	for (int timeTick = 0; timeTick < totalTime; timeTick++)
	{
		generatePassengers(timeTick);
		Lift::runOneTimeTick();
	}

	double waitTime = Lift::getAverageWaitTime();
	double transitTime = Lift::getAverageTransitTime();
	double time = Lift::getAverageTime();

	Lift::close();

	cout << "passenger count: " << Lift::getPassengerCount() << endl;
	cout << "average wait time: " << waitTime << endl;
	cout << "average transit time: " << transitTime << endl;
	cout << "average time: " << time << endl;

	cout << "test passenger count: " << testPassengerCount << endl;
	cout << "testTransitTimeCount: " << testTransitTimeCount << endl;
	cout << "test min transit time: " << (double) testTransitTimeCount / testPassengerCount << endl;
	cout << endl;

	return 0;
}
