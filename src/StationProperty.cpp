#include "../headers/StationProperty.h"
#include "../headers/UserAnimator.h"
#define RENT_STAGES 4 
int StationProperty::stationNumber = 0;
StationProperty::StationProperty(std::string name, int buyPrice, int updateCost,Groups groupId,int fileId):AbstractProperty(name, buyPrice, updateCost, groupId) {
	this->stationNumber = 0;
	this->rentStage = 0;
	this->texturePath = this->texturePath = "assets/station_properties/" + std::to_string(fileId) + ".bmp";
	this->mortgaged = false;
	this->mortgageVal = 100;
	rentPrices.push_back(25);
}
StationProperty::~StationProperty() {

}

void StationProperty::mortgage(Player* currentPlayer) {
	if (owner == currentPlayer) {	
		if (!mortgaged) {
		
			if (Game::isMortgagePressed()) {
				/*If it is an improved property, The player must destroy all the houses and hotels form the same colored tiles
				*/
				mortgaged = true;
				std::string message = "You have sold " + this->getName();
				UserAnimator::popUpMessage(message);
				owner->receiveMoney(mortgageVal);
				Game::setMortgagePressed(false);
			}
		}
		else {
			std::string msg = "It appears you have already mortgaged this property. Lifting the mortgage would mean paying \n The mortgage Value of the property + 10 % of its value for a total of  " + std::to_string(mortgageVal * 1.1);
			UserAnimator::popUpMessage(msg);
			
			int answer;
			
			if (Game::isBuyPressed()) {
				if (owner->getMoney() < buyPrice * 1.1) {
					msg =  " Insufficient Founds to complete action.\n";
					UserAnimator::popUpMessage(msg);
					return;
				}
				owner->payMoney(mortgageVal * 1.1);

				msg = "Mortgage lifted for " + name;
				UserAnimator::popUpMessage(msg);
				mortgaged = false;

			}
		}
	}
	else {
		std::string msg = "You do not own this property\n ";
		UserAnimator::popUpMessage(msg);

	}
}
//Function that will be called as a listener if the button "Buy" is pressed in game
void StationProperty::getMeAnOwner(Player* currentPlayer) {
	std::string msg;
	if (owner == nullptr) {
		//Checks if the player pressed the buy button 
		if (Game::isBuyPressed()) {
			if (currentPlayer->getMoney() < buyPrice) {
				msg = "Aquisition failed. Lack of funds `\( `-`)/` ";
				UserAnimator::popUpMessage(msg);
			}
			else {
				std::string message = currentPlayer->getName() + " bought " + name;
				UserAnimator::popUpMessage(message);
				owner = currentPlayer;
				currentPlayer->buyProperty(this,false);
			}
			Game::setBuyPressed(false);
		}
	}
	else {
		if (owner != currentPlayer && mortgaged) {
			msg = "Please Wait while " + currentPlayer->getName() + " and" + owner->getName() + "are negotiating for " + name;
			UserAnimator::popUpMessage(msg);
			currentPlayer->startTrade(owner);
			currentPlayer->setBuyerTradeFlag();
			owner->startTrade(currentPlayer);
			owner->setOwnerTradeFlag();
		}

		else {
			msg = "This station already has an owner\n";
			UserAnimator::popUpMessage(msg);
		}
	}
}
void StationProperty::doEffect(Player* currentPlayer) {
	std::string msg;
	if (owner == nullptr) {
		UserAnimator::popPropertyCard(this);
		std::string str = "Press 'Buy' if you want to buy this property.";

		UserAnimator::popUpMessage(str);
		getMeAnOwner(currentPlayer);
		return;
	}
	if (owner == currentPlayer) {
		mortgage(currentPlayer);
	}
	if (owner != currentPlayer) {
		int sumToPay = 0;
		sumToPay = owner->getOwnedStationsLength() * 25;
		rentPrices[0] = sumToPay;
		if (currentPlayer->getFlag() == 2) {
			msg = currentPlayer->getName() + " needs to pay TWICE  the  sum :" + std::to_string(sumToPay) + " to " + owner->getName();
			UserAnimator::popUpMessage(msg);
			owner->receiveMoney(2 * sumToPay);
			currentPlayer->payMoney( 2 * sumToPay);
		}
		else {
			if (!mortgaged) {
				
				msg = currentPlayer->getName() + " needs to pay " + std::to_string(sumToPay) + " to " + owner->getName();
				UserAnimator::popUpMessage(msg);
				owner->receiveMoney(sumToPay);
				currentPlayer->payMoney(sumToPay);
				UserAnimator::playerPaysPlayer(currentPlayer, owner);
			}
			else {
				msg = owner->getName() + " chose to mortgage this property, thus the is no rent to pay \n";
				UserAnimator::popUpMessage(msg);
			}
		}
	}
}
int StationProperty::getRentPrice() {
	return  rentPrices[0];
}

void StationProperty::print() {
	if (owner) {
		std::cout << name << " Rents for: " << getRentPrice();
		std::cout << "Current Owner : " << owner->getName();
		std::cout << mortgaged ? " Currentyl mortgaged" : " Currently not mortgaged";
	}
	else {
		std::cout << name << " Color: " << groupId << " Buys for: " << buyPrice << " Rents for: " << getRentPrice();
		std::cout << "Not Owned by Anoyone \n";
	}
}