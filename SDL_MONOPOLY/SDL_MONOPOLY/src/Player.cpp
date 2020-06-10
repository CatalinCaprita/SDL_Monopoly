#include "../headers/Player.h"
#include "../headers/HouseProperty.h"
#define OFFSET 3
#define DICE_MOVE 0
#define MUST_BE_JAILED 1
#define EXEC_COMMAND 2
#define OWNER_TRADE 3
#define BUYER_TRADE 4
#define NUM_COLORS 8
int Player::counter = 0;

//Could convert these into distance from X = 0 to a said X  in GAME UNITS
// 1 GAME UNIT .... WIDTH / 100 pixels
// x GAME UNITS ..... DISTANCE IN PIXELS FROM 0 TO SAID POSITIOn
//-> x = DISTANCE IN PIXELS / WIDTH * 100 GAME UNITS
//Could do measurements for one scalin in game units and then convert from there
//Then from 
// distance in pixels related to screen width = 

int coordX[] = { 91, 81, 73, 65, 57, 49, 41, 33, 25, 17,
				  8, 5, 5, 5, 5, 5, 5, 5, 5, 5,
				  6, 16, 24, 32, 40, 48, 56, 64, 72, 81,			// first substraction: 10 g.u ;		every substraction after: 8 g.u;
				  94, 92, 92, 92, 92, 92, 92, 92, 92, 92
				};
int coordY[] = { 91, 91, 91, 91, 91,  91, 91, 91, 91, 91,
				 92, 84, 74, 66, 58, 50, 42, 34, 26, 18,
				 6, 4, 4, 4, 4, 4, 4, 4, 4, 4,
				6, 16, 24, 32, 40, 48, 56, 64, 72, 80
				};
Groups houseColors[] = { BROWN, LTBLUE, PURPLE, ORANGE, RED, YELLOW, GREEN, BLUE };
//W, H, X, Y  will be in GAME_UNITS now, see Game.cpp and Sprite.h
Player::Player(std::string name, const char* filepath, int unitX, int unitY, int unitH, int unitW) : totalMoney(10000),id(counter + 1), currentPosition(0), name(name),bankrupt(false){
	counter++;
	sprite = new Sprite(filepath,unitW,unitH,unitX,unitY,-1,-1,true);
	sprite->setRenderDelay(350);
	remainingSteps = 0;
	finishMoving = false;
	flagType = DICE_MOVE;
	sumToAccept = -100;
}

Player::~Player() {
	delete sprite;
}
/*
Once finnished moving the player reaches a certain currentPosition
*/

void Player::move() {
	currentPosition++;
	if (currentPosition != currentPosition % 40)
	{
		std::cout << "Ai trecut de GO! Primesti 200 de BISTARI!" << std::endl;
		this->totalMoney += 200;
	}
	currentPosition %= 40;
	/*
		call of tiles[position??].doEffect(this);
	*/
}
//Every Drawable object will have its sizes in game units for scalablity. 1 game unit = screenSzie / 100;
void Player::setSpriteScale(int screenW, int screenH) {
	sprite->setScale(screenW,screenH);
}
/**
@params remainingSteps , firstDieValue + secondDieValue, how many steps the player has to move, i.e. how many times to update the sprite

*/
void Player::setRemainingSteps(int remainingSteps,int direction) {
	this->remainingSteps = remainingSteps;
	this->direction = direction;
}
Sprite* Player::getSprite() {
	return sprite;
}
std::string& Player::getName() {
	return name;
}


/*
Money and Property Interactions :
*/
int Player::getMoney() {
	return totalMoney;
}
int Player::receiveMoney(int amount) {
	this->totalMoney += amount;
	std::cout << name << " received " << amount << " money \n";
	return amount;
}

int Player::payMoney(int amount) {
	if (this->totalMoney < 0) {
		std::cout << "You are BANKRUPT!";
		return 0;
	}
	this->totalMoney -= amount;
	return amount;
}

void Player::buyProperty(Tile* property,bool byTrade)
{
	int buyPrice = dynamic_cast<AbstractProperty*>(property)->getBuyPrice();
	if (!byTrade && totalMoney < buyPrice)
		std::cout << "Sorry, you don't have the money!";
	else {
		if(!byTrade)
			this->payMoney(buyPrice);
		std::cout << name << " bought" << property->getName() << std::endl;
		auto it = ownedProperties.find(property->getGroupId());
		if (it == ownedProperties.end()) {
			std::vector<Tile*> item;
			ownedProperties.insert({ property->getGroupId(), item });
		}
		ownedProperties[property->getGroupId()].push_back(property);
		dynamic_cast<AbstractProperty*>(property)->setOwner(this);
	}
	return;
}
void Player::sellProperty(Tile* property)
{
	
}

int Player::getOwnedStations() {
	auto it = ownedProperties.find(STATION);
	if(it != ownedProperties.end())
		return ownedProperties[STATION].size();
	return 0;
}

int Player::getOwnedUtils() {
	auto it = ownedProperties.find(UTIL);
	if (it != ownedProperties.end())
		return ownedProperties[UTIL].size();
	return 0;
}

bool Player::ownsAllOfColor(Groups color) {
	auto pos = ownedProperties.find(color);
	if (pos == ownedProperties.end())
		return false;
	if (color == BROWN || color == BLUE)
		return ownedProperties[color].size() == 2;
	return ownedProperties[color].size() == 3;
}

void Player::destroyHousesFromColor(Groups color) {
	auto pos = ownedProperties.find(color);
	if (pos != ownedProperties.end())
	for (int i = 0; i < ownedProperties[color].size(); i++) {
		dynamic_cast<HouseProperty*>(ownedProperties[color][i])->destroyHouses();
	}
}
void Player::payPerBuildings() {
	int sumToPay = 0;
	for (int color = 0; color < NUM_COLORS; color++) {
		auto pos = ownedProperties.find(houseColors[color]);
		if (pos != ownedProperties.end())
			for (int i = 0; i < ownedProperties[houseColors[color]].size(); i++) {
				sumToPay += dynamic_cast<HouseProperty*>(ownedProperties[houseColors[color]][i])->getHousesPrice();
			}
	}
	std::cout << "Has to pay " << sumToPay<<std::endl;
	if (getMoney() < sumToPay) {
		std::cout << "Insufficient founds";
		return;
	}
	payMoney(sumToPay);
}

void Player::startTrade(Player* otherPlayer) {
	//The player that wants to buy the property will start the trade, namely it will set the flag of the property owner to buyer_trade
	tradeWith = otherPlayer;
	tradeWith->setTradeStatus(true);
	onGoing = true;
	
}
bool Player::onGoingTrade() {
	return onGoing;
}

void Player::setTradeStatus(bool status) {
	onGoing = status;
}
int Player::proposeSumFor(Tile * propWanted) {
	if (tradeWith != nullptr) {
		int answer = -1;
		std::cout <<name<< ": Please set what sum you propose for " << propWanted->getName() << ": ";
		bool valid = false;
		do {
			std::cin >> answer;
			if (answer < -1) {
				std::cout << "You are allowed to offer only positive amounts!\n";
			}
			if (answer > totalMoney) {
				std::cout << "You cannot offer more than you've got !\n";
			}

		} while (answer < -1 || answer > totalMoney);
		tradeWith->setProposedSum(answer);
		return answer;
	}
	return 0;
}

void Player::setProposedSum(int amount) {
	sumToAccept = amount;
}

/*
Asta se intampla doar cand playerul trebuie sa ajunga la Jail. O sa aibe cum ati zis voi 50 - currentPosition pozitii de mutat, iar cand termina de mutat,
remainingSteps == 0, atunci se initiaza goToJail
Totusi, in iteratiile Game::update() si Game::render() el figureaza ca mai are de mutat, deci il las sa mute. Flag-ul e pentru cand termina de mutat
*/

/*
Jail Functions
*/
void Player::goToJail() { 
	std::cout << name << " will GO TO JAIL !\n";
	setRemainingSteps((50 - this->getCurrentPosition()) % 40); //Player is now in moving, once it will finish, it will go direcly to jail
	jailTurnsLeft = 3;
} 
bool Player::isJailed()
{
	return !(jailTurnsLeft == 0);
}

void Player::freeFromJail()
{
	jailTurnsLeft = 0;
	flagType = DICE_MOVE;
	std::cout << name << " is now FREE \n";
}

void Player::setJailTurnsLeft(int turns)
{
	jailTurnsLeft = turns;
	std::cout << name << " will be out of the game for the next " << turns << std::endl;
}

int Player::getJailTurnsLeft()
{
	return jailTurnsLeft;
}
bool Player::isBankrupt()
{
	return bankrupt;
}

/*
Flag Setting Area
*/

int Player::getFlag() {
	return flagType;
}
void Player::setDiceFlag() {
	flagType = DICE_MOVE;
}
void Player::setJailFlag() {
	flagType = MUST_BE_JAILED;
}

void Player::setCommandFlag() {
	flagType = EXEC_COMMAND;
}

void Player::setBuyerTradeFlag() {
	flagType = BUYER_TRADE;
}

void Player::setOwnerTradeFlag() {
	flagType = OWNER_TRADE;
}

/*INTERNALS

/**
@returns currentPosition where the player lands if it has finished moving, stepsRemaining  = 0
*/
int Player::getCurrentPosition() {
	return currentPosition;
}
/**
@returns true if the player has moved since rolling the dice, i.e. moving animation should no longer be expected
Daca finishMoving e true, inseamna ca tot in aceeasi tura, in update trebuie sa se intample interactiunea cu Tile[currentPosition]
deci o sa intoarca true, dar seteaza imediat pe false
*/
bool Player::finishedMoving() {
	if (finishMoving) {
			finishMoving = false;
		return true;
	}
	return flagType == BUYER_TRADE;
}
/*
Player's Sprite Position will be updated only agter a delay, set by renderDelay
and only if it has more than 0 steps to move.
Otherwise player's sprite keeps its position
int direction - 1 forward, -1 backward
*/
void Player::update() {
	if (sprite->isClicked())
		std::cout << "Player Sprite Clicked!\n";
	if (sprite->canBeUpdated()) {
		/*
		Daca NU e Jailed, i.e. e deja in tile-ul jail SI mai are pasi de facut, atunci pozitia lui se updateaza
		*/
		if (!(flagType == BUYER_TRADE || flagType == OWNER_TRADE)) {
			if (!isJailed() && remainingSteps >0) {
				currentPosition += direction;
				if (currentPosition != currentPosition % 40) {
					std::cout << "Ai trecut de GO! Primesti 200 de BISTARI!" << std::endl;
					this->totalMoney += 200;
				}
				currentPosition %= 40;
				sprite->updateTo(coordX[currentPosition], coordY[currentPosition]);
				remainingSteps--;
				/*
				Cand nu mai are pasi de mutat, atunci, tot in Game::update() o sa arate ca urmeaza interactiunea cu tile[currentPositon]
				*/
				if (remainingSteps == 0)
					finishMoving = true;
				
				std::cout << "player " << name << " has to move " << remainingSteps << " steps \n ";
			}
		}
		else {
			if (flagType == OWNER_TRADE) {
				if (sumToAccept > -1) {
					std::cout << name<< ": Are you ok with " << sumToAccept << " ? Press 1 and you will sell the property for this sum.";
					int answer;
					std::cin >> answer;
					if (answer == 1) {
						tradeWith->payMoney(sumToAccept);
						tradeWith->setTradeStatus(false);
						receiveMoney(sumToAccept);
						setDiceFlag();
					}
					else {
						tradeWith->setTradeStatus(true);
					}
				}

			}
		}
		
	}
}

/**
See sprite->render();
*/
void Player::render() {
	sprite->render();
	
}

void Player::print(){
	std::cout << "name: " << name << "id: " << id << "balance: " << totalMoney << " owned properties: "<< std::endl;
	for (auto& type : ownedProperties) {
		std::cout << "All the " << type.first << " properties: \n";
		for (int i = 0; i < type.second.size(); i++) {
			type.second[i]->print();
			std::cout << std::endl;
		}
	}
}
