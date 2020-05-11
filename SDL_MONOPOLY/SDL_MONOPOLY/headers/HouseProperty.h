#ifndef HOUSEPROPERTY_H
#define HOUSEPROPERTY_H
#include <string>
#include <iostream>
#include <vector>
#include "AbstractProperty.h"
class HouseProperty  : public AbstractProperty{
public :
	HouseProperty(std::string name, int buyPrice,int updateCost,int mortgageVal,std::vector<int> &rentPrices,Groups groupId,int rectId);
	~HouseProperty();
	void update();
	void mortgage(Player* currentPlayer);
	void doEffect(Player* currentPlayer);
	void print();
	void setRentPrice(int idx, int price);
	void render() override;
	void destroyHouses();
	int getRentPrice() {
		return rentPrices[rentStage];
	}
	bool isRenderable() override;
	void getMeAnOwner(Player* currentPlayer);
private:
	int houseNumber;
	bool hasHotel;
	bool renderable;
	bool mortgaged;
	int houseOrientation;
	int mortgageVal;

	Sprite* houses[4];


};
#endif // !HOUSEPROPERTY_H
