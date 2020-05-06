#include "../headers/StationProperty.h"
#include "../headers/UserAnimator.h"
#define RENT_STAGES 4 
int StationProperty::stationNumber = 0;
StationProperty::StationProperty(std::string name, int buyPrice, int updateCost,Groups groupId,int fileId):AbstractProperty(name, buyPrice, updateCost, groupId) {
	this->stationNumber = 0;
	this->rentStage = 0;
	this->texturePath = this->texturePath = "assets/station_properties/" + std::to_string(fileId) + ".bmp";
	rentPrices.push_back(25);
}
StationProperty::~StationProperty() {

}

void StationProperty::doEffect(Player* currentPlayer) {
	if (owner == nullptr) {
		UserAnimator::popPropertyCard(this);
		std::cout << "This property is not owned by anyone. Do you wish to buy it? 1/0.\n";
		int answer;
		std::cin >> answer;
		if (answer == 1) {
			if (currentPlayer->getMoney() < buyPrice) {
				std::cout << " Aquisition failed. Lack of funds `\( `-`)/` ";
			}
			else {
				owner = currentPlayer;
				currentPlayer->buyProperty(this, "station");
			}
		}
		return;
	}
	if (owner != currentPlayer) {
		int sumToPay = 0;
		sumToPay = owner->getOwnedStations() * 25;
		rentPrices[0] = sumToPay;
		if (currentPlayer->getFlag() == 2) {
			std::cout << currentPlayer->getName() << " needs to pay TWICE  the  sum :" << sumToPay << " to " << owner->getName() << std::endl;
			owner->receiveMoney(2 * sumToPay);
			currentPlayer->payMoney( 2 * sumToPay);
		}
		else {
			std::cout << currentPlayer->getName() << " needs to pay " << sumToPay << " to " << owner->getName() << std::endl;
			owner->receiveMoney(sumToPay);
			currentPlayer->payMoney(sumToPay);
		}
	}
}
int StationProperty::getRentPrice() {
	return  rentPrices[0];
}

void StationProperty::print() {
	std::cout << name << " Buys for: " << buyPrice << " Rents for: " << getRentPrice() << std::endl;
}