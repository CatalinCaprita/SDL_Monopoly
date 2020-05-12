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
	void mortgage(Player* currentPlayer);
	int getRentPrice();
	void print();
	void getMeAnOwner(Player* currentPlayer);
private:
	static int stationNumber;
	bool mortgaged;
	int mortgageVal;
};

#endif // !STATIONPROPERTY_H