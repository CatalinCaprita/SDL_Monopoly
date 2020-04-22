#ifndef UTILITYPROPERTY_H
#define UTILITYPROPERTY_H
#include <string>
#include <iostream>
#include "AbstractProperty.h"
#include <vector>
class UtilityProperty : public AbstractProperty {
public:
	UtilityProperty(std::string name, int buyPrice, int updateCost, std::vector<int>& rentPrices, Groups groupId);
	~UtilityProperty();
	void doEffect(Player* currentPlayer);
private:
	
};
#endif // !UTILITYPROPERTY_H
