#include "../headers/Properties.h"
#include "../headers/Corner.h"
#include "../headers/UserAnimator.h"
Corner::Corner(std::string& name, std::string& command,int cornerNo):Tile(name){
	this->command = command;
	this->cornerNo = cornerNo;
	this->groupId = CORNER;
}

Corner::~Corner() {

}

void Corner::getMeAnOwner(Player* currentPlayer) {
	return;
}

void Corner::mortgage(Player* currentPlayer) {
	return;
}

void Corner::doEffect(Player * currentPlayer) {
	UserAnimator::popUpMessage(command);
	switch (cornerNo) {
	case 0:
		std::cout << currentPlayer->getName() << " passed START. It will recieve 200\n";
		break;
	case 3:
		
		if (currentPlayer->getCurrentPosition() > 10)
			currentPlayer->setRemainingSteps((currentPlayer->getCurrentPosition() - 10) % 40, -1);
		else
			currentPlayer->setRemainingSteps(10 - currentPlayer->getCurrentPosition());
		currentPlayer->setJailFlag();//Player will remain to Jail;
		//currentPlayer->goToJail();
		break;
		
	}

}