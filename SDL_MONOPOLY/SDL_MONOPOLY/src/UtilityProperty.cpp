#include "../headers/UtilityProperty.h"
#include  "../headers/Player.h"
#include "../headers/UserAnimator.h"
#include "../headers/Game.h"
UtilityProperty::UtilityProperty(std::string name, int buyPrice, int updateCost,Groups groupId,int fileId) :AbstractProperty(name, buyPrice, updateCost, groupId) {
	this->rentStage = 0;
	this->texturePath = "assets/utility_properties/" + std::to_string(fileId)+ ".bmp";
}
UtilityProperty::~UtilityProperty() {

}
//Function that will be called as a listener if the button "Buy" is pressed in game
void UtilityProperty::getMeAnOwner(Player* currentPlayer) {
	if (owner == nullptr) {
		//Checks if the player pressed the buy button 
		if (Game::isBuyPressed()) {
			if (currentPlayer->getMoney() < buyPrice) {
				std::cout << " Aquisition failed. Lack of funds `\( `-`)/` ";
			}
			else {
				owner = currentPlayer;
				currentPlayer->buyProperty(this, "utility");
			}
			Game::setBuyPressed(false);
		}
	}
	else {
		std::cout << "This utility already has an owner\n";
	}
}

void UtilityProperty::doEffect(Player* currentPlayer) {
	if (owner == nullptr) {
		UserAnimator::popPropertyCard(this);
		getMeAnOwner(currentPlayer);
		return;
	}
	if (owner != currentPlayer) {
		int multiplier = 4;
		switch (owner->getOwnedUtils()) {
		case(1):
			multiplier = 4;
			break;
		case(2):
			multiplier = 10;
			break;
		}
		int sumToPay = multiplier * getRentPrice();
		if (currentPlayer->getMoney() >= sumToPay) {
			std::cout << currentPlayer->getName() << " needs to pay " << sumToPay << " to " << owner->getName() << std::endl;
			owner->receiveMoney(sumToPay);
			currentPlayer->payMoney(sumToPay);
		}
		else {
			std::cout << currentPlayer->getName() << " cannot pay the rent.";
		}
		
	}
}
void UtilityProperty::print() {
	std::cout << name << " Buys for: " << buyPrice << " Rents for: " << getRentPrice() << std::endl;
}

int UtilityProperty::getRentPrice() {
	
	return Game::getDice()->getFirstDieValue() + Game::getDice()->getSecondDieValue();
}