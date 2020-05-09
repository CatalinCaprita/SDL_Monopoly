#include "../headers/AbstractProperty.h"
#include "../headers/Player.h"
AbstractProperty::AbstractProperty(std::string name, int buyPrice, int updateCost,Groups groupId) : Tile(name,groupId){
	
	this->buyPrice = buyPrice;
	this->owner = NULL;
	this->updateCost = updateCost;
	this->rentStage = 0;

}

int AbstractProperty::getBuyPrice() {
	return buyPrice;
}


Player* AbstractProperty::getOwner() {
	return owner;
}
