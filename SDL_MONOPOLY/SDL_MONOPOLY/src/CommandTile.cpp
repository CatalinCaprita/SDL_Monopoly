#include "../headers/Properties.h"
#include "../headers/Player.h"
#include "../headers/UserAnimator.h"
#include <vector>
#include <string>
#include <chrono>
#include <time.h>
#define COMMANDS_SIZE 15

std::string allCommands[] = {
	"Go to Start! Collect 200.", //
	"Advance to Illinois Ave. If you pass Go, collect $200",
	"Advance to St. Charles Place. If you pass Go, collect $200",
	"Advance token to nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.",
	"Advance token to the nearest Railroad and pay owner twice the rental to which he/she is otherwise entitled. If Railroad is unowned, you may buy it from the Bank.",
	"Bank pays you dividend of $50",
	"Get Out of Jail Free",
	"Go Back 3 Spaces",
	"Go to Jail.Go directly to Jail. Do not pass Go, do not collect $200",
	"Make general repairs on all your property.For each house pay $25. For each hotel $100",
	"Pay poor tax of $15"
	"Take a trip to Reading Railroad.If you pass Go, collect $200",
	"Take a walk on the Boardwalk.Advance token to Boardwalk",
	"You have been elected Chairman of the Board.Pay each player pays you $50",
	"You have won a crossword competition.Collect $100",
	"Your building and loan matures.Collect $150"
};

std::queue <int> CommandTile::chanceQ;
std::queue< int>CommandTile::communityQ;
bool CommandTile::initialized = false;

void CommandTile::shuffle(std::queue<int>&whichQ) {
	std::string msg;
	std::cout << "Suffling Community Chest and Chance decks\n";
	int indexes[COMMANDS_SIZE];
	for (int i = 0; i < COMMANDS_SIZE; i++) {
		indexes[i] = i;
	}
	std::random_shuffle(indexes, indexes + COMMANDS_SIZE);
	for (int i = 0; i < COMMANDS_SIZE; i++) {
		whichQ.push(indexes[i]);
	}
}

void CommandTile::getMeAnOwner(Player* currentPlayer) {
	return;
}

void CommandTile::mortgage(Player* currentPlayer) {

}

CommandTile::CommandTile(const std::string& name) : Tile(name) {
	if (!initialized) {
		shuffle(communityQ);
		shuffle(chanceQ);
		initialized = true;
	}
	if (name == "Chance"){
		backTexturePath = "assets/commands/chanceBack.bmp";
		texturePath = "assets/commands/chanceBack.bmp";
		destX = 74;
		destY = 61;
		groupId = CHANCE;
	}
	else 
		if(name == "Community Chest"){
		backTexturePath = "assets/commands/communityChestBack.bmp";
		texturePath = "assets/commands/communityChestBack.bmp";
		destX = 29;
		destY = 17;
		groupId = CHEST;
		}
	else 
		if (name == "Income Tax") {
		backTexturePath = frontTexturePath = "assets/commands/incomeTax.bmp";
		texturePath = "assets/commands/incomeTax.bmp";
		groupId = INC_TAX;
		}
	else {
		backTexturePath = frontTexturePath = "assets/commands/luxTax.bmp";
		texturePath = "assets/commands/luxTax.bmp";
		groupId = LUX_TAX;
	}
	//upon initialization the texture path will be just the folder name;
	
}
void CommandTile::print() {
	std::cout << "Card Type is :" << name << ", thus its animation starts at (" << destX << "," << destY << ")\n";
}
void CommandTile::doEffect(Player *currentPlayer) {
	std::string msg;
	if (groupId == LUX_TAX) {
		UserAnimator::popPropertyCard(this);
		msg =  "LUXURY TAX. PAY 100$ \n";
		UserAnimator::popUpMessage(msg);
		currentPlayer->payMoney(100);
		SDL_Delay(500);
		return;
	}
	if (groupId == INC_TAX) {
		UserAnimator::popPropertyCard(this);
		msg = "INCOME TAX. PAY 200$ \n";
		UserAnimator::popUpMessage(msg);
		currentPlayer->payMoney(200);
		SDL_Delay(500);
		return;
	}
	//frontTexturePath = texturePath + std::to_string(randomExtraction) + ".bmp";
	//TO DO : ANIMATION FOR THE COMMAND TILE WITH ITS BACK
	int index;
	UserAnimator::popPropertyCard(this);
	if (groupId == CHEST) {
		index = CommandTile::communityQ.front();
		CommandTile::communityQ.pop();
		CommandTile::communityQ.push(index);
	}
	else {
		index = CommandTile::chanceQ.front();
		CommandTile::chanceQ.pop();
		CommandTile::chanceQ.push(index);
	}
	std::string command = allCommands[index];
	UserAnimator::popUpMessage(command);
	switch (index) {
	/*If they are Queues, how do you know the index for the command??
	 - i thought maybe transform each string
	*/
	case 0:
		currentPlayer->setRemainingSteps(40 - currentPlayer->getCurrentPosition());
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 1:
		currentPlayer->setRemainingSteps((40 + 24 - currentPlayer->getCurrentPosition()) % 40 );
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 2:
		currentPlayer->setRemainingSteps((40 + 11 - currentPlayer->getCurrentPosition()) % 40);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 3:
		if( 12 < currentPlayer->getCurrentPosition()  && currentPlayer->getCurrentPosition() < 28 )
			currentPlayer->setRemainingSteps((28 - currentPlayer->getCurrentPosition()) % 40);
		else
			currentPlayer->setRemainingSteps((40 + 12 - currentPlayer->getCurrentPosition()) % 40);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 4: {
		int position = currentPlayer->getCurrentPosition() / 5;
		position = (position % 2 == 0) ?  ((position + 1) * 5): ((position + 2 )* 5);
		currentPlayer->setRemainingSteps((position  - currentPlayer->getCurrentPosition()) % 40);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	}
	case 5:
		std::cout << currentPlayer->getName() << " recieves 50";
		currentPlayer->receiveMoney(50);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 6:
		currentPlayer->freeFromJail();
	
	case 7: 
		currentPlayer->setRemainingSteps(3,-1);
		currentPlayer->setCommandFlag();
		break;
	case 8:
		if (currentPlayer->getCurrentPosition() > 10)
			currentPlayer->setRemainingSteps((currentPlayer->getCurrentPosition() - 10) % 40, -1);
		else
			currentPlayer->setRemainingSteps(10 - currentPlayer->getCurrentPosition());
		currentPlayer->setJailFlag();//Player will remain to Jail;
		break;
	case 9:
		currentPlayer->payPerBuildings();
		currentPlayer->setCommandFlag();//Player must advance to start
		break;
	case 10:
		if (!currentPlayer->isBankrupt())
			currentPlayer->payMoney(15);
		break;
	case 11:
		currentPlayer->setRemainingSteps((40 + 5 - currentPlayer->getCurrentPosition()) % 40);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 12:
		currentPlayer->setRemainingSteps((40 + 39 - currentPlayer->getCurrentPosition()) % 40);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 13:
		currentPlayer->receiveMoney(200);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 14:
		currentPlayer->receiveMoney(100);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	case 15:
		currentPlayer->receiveMoney(100);
		currentPlayer->setCommandFlag();//Player must advance to start;
		break;
	}
}