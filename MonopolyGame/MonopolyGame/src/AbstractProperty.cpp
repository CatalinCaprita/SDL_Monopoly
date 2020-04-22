#include "../headers/AbstractProperty.h"
#include "../headers/Player.h"
AbstractProperty::AbstractProperty(std::string name, int buyPrice, int updateCost,Groups groupId) : Tile(name){
	
	this->buyPrice = buyPrice;
	this->owner = NULL;
	this->groupId = groupId;
	this->updateCost = updateCost;
	this->rentStage = 0;

}

int AbstractProperty::getBuyPrice() {
	return buyPrice;
}

int AbstractProperty::getGroupId() {
	return groupId;
}

Player* AbstractProperty::getOwner() {
	return owner;
}
