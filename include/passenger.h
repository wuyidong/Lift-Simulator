#ifndef PASSENGER_H
#define PASSENGER_H

#define PASSENGER_MAX_WEIGHT 100	// 100 kg

class Passenger {
private:
	int startFloor;
	int desFloor;
	int startTime;
	int boardTime;
	int getoffTime;

	float weight;

public:
	Passenger(int weight, int startFloor, int desFloor);

	inline void setStartTime(int time) { startTime = time;}
	inline void setBoardTime(int time) { boardTime = time;}
	inline void setGetoffTime(int time) { getoffTime = time;}

	inline int getStartFloor() { return startFloor;}
	inline int getDesFloor() { return desFloor;}
	inline int getStartTime() { return startTime;}
	inline int getBoardTime() { return boardTime;}
	inline int getGetoffTime() { return getoffTime;}
	inline float getWeight() { return weight;}
};

#endif
