#ifndef UTILITYPROPERTY_H
#define UTILITYPROPERTY_H
#include <string>
#include <iostream>
#include "AbstractProperty.h"
#include <vector>
class UtilityProperty : public AbstractProperty {
public:
	UtilityProperty(std::string name, int buyPrice, int updateCost, Groups groupId,int fileId);
	~UtilityProperty();
	void doEffect(Player* currentPlayer);
	void print();
	int getRentPrice();
	virtual void getMeAnOwner(Player* currentPlayer);
private:
	
};
#endif // !UTILITYPROPERTY_H
