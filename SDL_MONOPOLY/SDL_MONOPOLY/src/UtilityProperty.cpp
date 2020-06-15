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
	std::string msg;
	if (owner == nullptr) {
		//Checks if the player pressed the buy button 
		if (Game::isBuyPressed()) {
			if (currentPlayer->getMoney() < buyPrice) {
				msg = "Aquisition failed. Lack of funds `\( `-`)/`";
				UserAnimator::popUpMessage(msg);
			}
			else {
				std::string message = currentPlayer->getName() + " bought " + name;
				UserAnimator::popUpMessage(message);
				owner = currentPlayer;
				currentPlayer->buyProperty(this, "utility");
			}
			Game::setBuyPressed(false);
		}
	}
	else {
		msg = "This utility already has an owner\n";
		UserAnimator::popUpMessage(msg);
	}
}

void UtilityProperty::doEffect(Player* currentPlayer) {
	std::string msg;
	if (owner == nullptr) {
		UserAnimator::popPropertyCard(this);
		msg = "Press 'Buy' if you want to buy this property.";

		UserAnimator::popUpMessage(msg);
		getMeAnOwner(currentPlayer);
		return;
	}
	if (owner != currentPlayer) {
		int multiplier = 4;
		switch (owner->getOwnedUtilsLength()) {
		case(1):
			multiplier = 4;
			break;
		case(2):
			multiplier = 10;
			break;
		}
		int sumToPay = multiplier * getRentPrice();
		if (currentPlayer->getMoney() >= sumToPay) {
			msg = currentPlayer->getName() + " needs to pay " + std::to_string(sumToPay) + " to " + owner->getName();
			UserAnimator::popUpMessage(msg);
			owner->receiveMoney(sumToPay);
			currentPlayer->payMoney(sumToPay);
			UserAnimator::playerPaysPlayer(owner, currentPlayer);
		}
		else {
			msg = currentPlayer->getName() + " cannot pay the rent.";
			UserAnimator::popUpMessage(msg);
		}
		
	}
}
void UtilityProperty::print() {
	std::cout << name << " Buys for: " << buyPrice << " Rents for: " << getRentPrice() << std::endl;
}

void UtilityProperty::mortgage(Player* currentPlayer) {

}

int UtilityProperty::getRentPrice() {
	
	return Game::getDice()->getFirstDieValue() + Game::getDice()->getSecondDieValue();
}