#pragma once
#include "../headers/Tile.h"
#include "../headers/Player.h"
#include "Groups.h"
#include <string>
#include <vector>
class AbstractProperty : public Tile{

protected:
	int buyPrice;
	int updateCost;
	int rentStage; //pointer for rentPrices
	std::vector<int> rentPrices;
	Groups groupId;
	Player *owner;
	
public:
	//Let every kind of AbstractProperty have its own size for rentPrices[]
	AbstractProperty(std::string name, int buyPrice,int updateCost, Groups groupId);
	virtual void doEffect(Player* currentPlayer) = 0;
	virtual int getRentPrice() { return 0; };
	int getBuyPrice();
	int getGroupId();
	virtual void update() {};
	Player* getOwner();
	
};

