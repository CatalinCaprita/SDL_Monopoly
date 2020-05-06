#include "../headers/HouseProperty.h"
#include "../headers/Player.h"
#include "../headers/UserAnimator.h"
#define MAX_HOUSES 4
#define RENT_STAGES 6
HouseProperty::HouseProperty(std::string name, int buyPrice,int updateCost,std::vector<int>& rents, Groups groupId,int rectId) :AbstractProperty(name,buyPrice,updateCost,groupId){
	this->houseNumber = 0;
	this->hasHotel = false;
	this->rentStage = 0;
	this->texturePath = "assets/house_properties/" + std::to_string(rectId)+ ".bmp";
	//[ NO HOUSE, ONE HOUSE, TWO_HOUSES, THREE_HOUSES, FOUR_HOUSES, HOTEL]
	for (int i = 0; i < RENT_STAGES; i++) {
		rentPrices.push_back(rents[i]);
	}
}
HouseProperty::~HouseProperty() {

}
void HouseProperty::update() {
	//TO DO -- int answer = UserDialog::tileUpdateDialog()
	//Enters the function that calls Animator::tileUpdateAnimation()
	//Waits for user input on " Want to update this Property to X houses? "
	//if(answer == 1){
	if (rentStage < rentPrices.size() - 1) {
		std::cout << "Do you want to update ? 1/0 " << rentPrices.size() << std::endl;
		int answer;
		std::cin >> answer;
		if (answer == 1) {
			int paid = owner->payMoney(updateCost);
			if (paid > 0) {
				rentStage++;
				if (houseNumber < MAX_HOUSES) {
					houseNumber++;
					std::cout << "Property Updated. " << name << " now has" << houseNumber << " houses and rets for " << getRentPrice() << std::endl;
				}
				else {
					std::cout << "It appears" << name << " has already maximum number of houses. Update to a Hotel instead ? 1/0";
					int answer2;
					std::cin >> answer2;
					/*TO DO -- CHECK IF A PLAYER OWNS ALL THE COLORED PROPERTIES
					if (!currentPlayer->ownsAll(groupId)) {
						std::cout << "Cannot update to a hotel because you do not possess all " << groupId << " properties.";
						return;
					}
					*/
					std::cout << "Property Updated. " << name << " now has one hotel and rents for " << getRentPrice() << std::endl;
				}
			}
			else {
				std::cout << "Update failed due to bakruptcy" << std::endl;
			}
		}
	}
	
}
void HouseProperty::doEffect(Player* currentPlayer) {
	//calls Animator::tileExpandAnimation()
	std::cout << currentPlayer->getName() <<" stepped on " << name << std::endl;
	if (owner == currentPlayer && rentStage < rentPrices.size() - 1) {
		update();
	}
	else if (owner == NULL) {
		// int answer = UserDialog::purchasePropertyDialog()
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
				currentPlayer->buyProperty(this, "house");
			}
		}
		UserAnimator::fadePropertyCard(this);
	}
	else if(currentPlayer != owner){
			std::cout << currentPlayer->getName() << " needs to pay " << getRentPrice() << " to " << owner->getName() << std::endl;
			UserAnimator::playerPaysPlayer(currentPlayer, owner);
		owner->receiveMoney(getRentPrice());
		currentPlayer->payMoney(getRentPrice());
	}
}
void HouseProperty::print() {
	std::cout << name <<" Color: "<< groupId <<" Buys for: " << buyPrice << " Rents for: " << getRentPrice()<< " Has houses: " << houseNumber<<std::endl;
}
