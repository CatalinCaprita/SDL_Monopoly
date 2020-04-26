#include "../headers/Player.h"
#define OFFSET 3

int Player::counter = 0;

//Could convert these into distance from X = 0 to a said X  in GAME UNITS
// 1 GAME UNIT .... WIDTH / 100 pixels
// x GAME UNITS ..... DISTANCE IN PIXELS FROM 0 TO SAID POSITIOn
//-> x = DISTANCE IN PIXELS / WIDTH * 100 GAME UNITS
//Could do measurements for one scalin in game units and then convert from there
//Then from 
// distance in pixels related to screen width = 
int coordX[] = { 950, 820, 738, 656, 574, 492, 410, 328, 246, 164, 20,
				 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				 164, 246, 328, 410, 492, 574, 656, 738, 820, 950,			// first substraction: 130;		every substraction after: 82;
				 940, 940, 940, 940, 940, 940, 940, 940, 940, 940,
				};
int coordY[] = { 940, 940, 940, 940, 940, 940, 940, 940, 940, 940, 960,
				 820, 738, 656, 574, 492, 410, 328, 246, 164, 60,
				 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				 164, 246, 328, 410, 492, 574, 656, 738, 820, 950
				};

//W, H, X, Y  will be in GAME_UNITS now, see Game.cpp and Sprite.h
Player::Player(std::string name, const char* filepath, int unitX, int unitY, int unitH, int unitW) : totalMoney(10000),id(counter + 1), currentPosition(0), name(name), jailed(false),bankrupt(false){
	ownedProperties = *(new std::vector<Tile*>);
	counter++;
	sprite = new Sprite(filepath,unitW,unitH,unitX,unitY);
	remainingSteps = 0;
	finishMoving = false;
	renderDelay = 300;
	lastRender = 0;
}

Player::~Player() {
	delete sprite;
}
/*
Once finnished moving the player reaches a certain currentPosition
*/

//Every Drawable object will have its sizes in game units for scalablity. 1 game unit = screenSzie / 100;
void Player::setSpriteScale(int screenW, int screenH) {
	sprite->setScale(screenW,screenH);
}
/**
@params remainingSteps , firstDieValue + secondDieValue, how many steps the player has to move, i.e. how many times to update the sprite

*/
void Player::setRemainingSteps(int remainingSteps) {
	this->remainingSteps = remainingSteps;
}
Sprite* Player::getSprite() {
	return sprite;
}

/**
@returns true if the player has moved since rolling the dice, i.e. moving animation should no longer be expected
*/
bool Player::finishedMoving() {
	return finishMoving;
}
int Player::receiveMoney(int amount) {
	this->totalMoney += amount;
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
/**
@returns currentPosition where the player lands if it has finished moving, stepsRemaining  = 0
*/
int Player::getCurrentPosition() {
	return currentPosition;
}
void Player::buyProperty(Tile* property)
{
	if (totalMoney < ((AbstractProperty*)property)->getRentPrice())
		std::cout << "Sorry, you don't have the money!";
	else {
		this->payMoney(((AbstractProperty*)property)->getRentPrice());
		this->ownedProperties.push_back(property);
	}
	return;
}
void Player::sellProperty(Tile* property)
{
	for (int i=0;i<ownedProperties.size();i++)
		if (ownedProperties[i] == property)
		{
			//property->setOwner(NULL);
			// remove every layer of
			ownedProperties.erase(ownedProperties.begin()+i); // erases the element at index i -> needs testing

		}
}

std::string& Player::getName() {
	return name;
}

void Player::getJailed() {
	currentPosition = 10;
	jailed = true;
}
bool Player::isJailed()
{
	return jailed;
}


bool Player::isBankrupt()
{
	return bankrupt;
}

/*
Player's Sprite Position will be updated only agter a delay, set by renderDelay
and only if it has more than 0 steps to move. 
Otherwise player's sprite keeps its position
*/
void Player::update() {
	if (SDL_GetTicks() - lastRender >= renderDelay) {
		if (!jailed && remainingSteps > 0) {
			currentPosition++;
			currentPosition %= 40;
			//sprite->update(coordX[currentPosition] + (id - OFFSET) * 10, coordY[currentPosition]);
			sprite->update(-1, -1);
			remainingSteps--;
			if (remainingSteps == 0)
				finishMoving = true;
			lastRender = SDL_GetTicks();
			std::cout << "player " << name << " has to move " << remainingSteps << " steps \n ";
		}
		else {
			sprite->update(0, 0);
			finishMoving = false;
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
	std::cout << "name: " << name << "id: " << id << "balance: " << totalMoney << "owned properties: ";
	for (auto x : ownedProperties)
		std::cout << x->getName() + "; ";
}
