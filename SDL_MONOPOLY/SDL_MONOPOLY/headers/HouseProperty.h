#ifndef HOUSEPROPERTY_H
#define HOUSEPROPERTY_H
#include <string>
#include <iostream>
#include "AbstractProperty.h"
#include <vector>
class HouseProperty  : public AbstractProperty{
public :
	HouseProperty(std::string name, int buyPrice,int updateCost,std::vector<int> &rentPrices,Groups groupId);
	~HouseProperty();
	void update();
	void doEffect(Player* currentPlayer);
	void print();
	void setRentPrice(int idx, int price);
	int getRentPrice() {
		return rentPrices[rentStage];
	}
private:
	int houseNumber;
	bool hasHotel;


};
#endif // !HOUSEPROPERTY_H
