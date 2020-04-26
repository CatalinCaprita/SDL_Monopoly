#ifndef STATIONPROPERTY_H
#define STATIONPROPERTY_H
#include <string>
#include <iostream>
#include "AbstractProperty.h"
#include <vector>
class StationProperty :public AbstractProperty{

public:
	StationProperty(std::string name, int buyPrice, int updateCost,Groups groupId,int fileId);
	~StationProperty();
	void doEffect(Player* currentPlayer);
	void update(){}
	int getRentPrice();
	void print();
private:
	static int stationNumber;
};

#endif // !STATIONPROPERTY_H