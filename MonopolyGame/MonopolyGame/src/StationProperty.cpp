#include "../headers/StationProperty.h"
StationProperty::StationProperty(std::string name, int buyPrice, int updateCost, std::vector<int>& rents, Groups groupId) :AbstractProperty(name, buyPrice, updateCost, groupId) {
	this->stationNumber = 0;
	this->rentStage = 0;
}
StationProperty::~StationProperty() {

}

void StationProperty::doEffect(Player* currentPlayer) {
	if (owner == nullptr) {
		std::cout << "This property is not owned by anyone. Do you wish to buy it? 1/0.\n";
		int answer;
		std::cin >> answer;
		if (answer == 1) {
			///TODO PAY THE PRICE
			owner = currentPlayer;
			std::cout << currentPlayer->getName() << " bought" << name << std::endl;
		}
		return;
	}
	if (owner != currentPlayer) {
		int sumToPay = 0;
		//TODO functions that returns number of owned stations by the owner
		/*
		sumToPay = owner.getNumberOfStations() * 25;
		*/
		std::cout << currentPlayer->getName() << " needs to pay " << sumToPay << " to " << owner->getName() << std::endl;
		owner->recieveMoney(sumToPay);
		currentPlayer->payMoney(sumToPay);

	}
}