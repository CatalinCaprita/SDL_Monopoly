#ifndef STATIONPROPERTY_H
#define STATIONPROPERTY_H
#include <string>
#include <iostream>
#include "AbstractProperty.h"
#include <vector>
class StationProperty :public AbstractProperty{

public:
	StationProperty(std::string name, int buyPrice, int updateCost, std::vector<int>& rentPrices, Groups groupId);
	~StationProperty();
	void doEffect(Player* currentPlayer);
private:
	static int stationNumber;
};

#endif // !STATIONPROPERTY_H