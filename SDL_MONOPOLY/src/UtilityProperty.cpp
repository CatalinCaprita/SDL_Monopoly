#include "../headers/UtilityProperty.h"
#include  "../headers/Player.h"
UtilityProperty::UtilityProperty(std::string name, int buyPrice, int updateCost, std::vector<int>& rents, Groups groupId) :AbstractProperty(name, buyPrice, updateCost, groupId) {
	this->rentStage = 0;
}
UtilityProperty::~UtilityProperty() {

}

void UtilityProperty::doEffect(Player* currentPlayer) {
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
		int multiplier = 4;
		//TODO check if player has both utilities or just one
		/*int numberOfUtilities = owner.getNumberOfUtilities();
		switch (numberOfUtilities) {
		case(1):
			multiplier = 4;
			break;
		case(2):
			multiplier = 10;
			break;
		}
		*/
		int sumToPay = 0;
		//TODO SA AVEM O FUNCTIE CARE NE RETURNEAZA SUMA ZARURILOR
		//sumToPay = multiplier * OCLASA.getSumDice();
		std::cout << currentPlayer->getName() << " needs to pay " << sumToPay << " to " << owner->getName() << std::endl;
		owner->recieveMoney(sumToPay);
		currentPlayer->payMoney(sumToPay);
		
	}
}