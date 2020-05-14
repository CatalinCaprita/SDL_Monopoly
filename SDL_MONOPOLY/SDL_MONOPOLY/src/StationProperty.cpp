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
				owner->receiveMoney(mortgageVal);
				Game::setMortgagePressed(false);
			}
		}
		else {
			std::cout << "It appears you have already mortgaged this property. Lifting the mortgage would mean paying " <<
				"The mortgage Value of the property + 10 % of its value for a total of  " << mortgageVal * 1.1 << ". Proceed? (1/0).";
			int answer;
			std::cin >> answer;
			if (answer == 1) {
				if (owner->getMoney() < buyPrice * 1.1) {
					std::cout << " Insufficient Founds to cpmlete action.\n";
					return;
				}
				owner->payMoney(mortgageVal * 1.1);
				std::cout << "Mortgage lifted for " << name << "\n";
				mortgaged = false;

			}
		}
	}
	else {
		std::cout << "You do not own this property\n";
	}
}
//Function that will be called as a listener if the button "Buy" is pressed in game
void StationProperty::getMeAnOwner(Player* currentPlayer) {
	if (owner == nullptr) {
		std::cout << "Im almost in\n";
		//Checks if the player pressed the buy button 
		if (Game::isBuyPressed()) {
			std::cout << "Im in\n";
			if (currentPlayer->getMoney() < buyPrice) {
				std::cout << " Aquisition failed. Lack of funds `\( `-`)/` ";
			}
			else {
				owner = currentPlayer;
				currentPlayer->buyProperty(this, "station");
			}
			Game::setBuyPressed(false);
		}
	}
	else {
		if (owner != currentPlayer && mortgaged) {
			std::cout << "Please Wait while " << currentPlayer->getName() << " and" << owner->getName() << "are negotiating for " << name << std::endl;
			currentPlayer->startTrade(owner);
			currentPlayer->setBuyerTradeFlag();
			owner->startTrade(currentPlayer);
			owner->setOwnerTradeFlag();
		}

		else {
			std::cout << "This station already has an owner\n";
		}
	}
}
void StationProperty::doEffect(Player* currentPlayer) {
	if (owner == nullptr) {
		UserAnimator::popPropertyCard(this);
		
		getMeAnOwner(currentPlayer);
		return;
	}
	if (owner == currentPlayer) {
		mortgage(currentPlayer);
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
			if (!mortgaged) {
				std::cout << currentPlayer->getName() << " needs to pay " << sumToPay << " to " << owner->getName() << std::endl;
				owner->receiveMoney(sumToPay);
				currentPlayer->payMoney(sumToPay);
				UserAnimator::playerPaysPlayer(currentPlayer, owner);
			}
			else {
				std::cout << owner->getName() << " chose to mortgage this property, thus the is no rent to pay \n";
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