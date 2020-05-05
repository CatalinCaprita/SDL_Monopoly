#include "../headers/Player.h"
#define OFFSET 3
#define DICE_MOVE 0
#define MUST_BE_JAILED 1
#define EXEC_COMMAND 2

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

//W, H, X, Y  will be in GAME_UNITS now, see Game.cpp and Sprite.h
Player::Player(std::string name, const char* filepath, int unitX, int unitY, int unitH, int unitW) : totalMoney(10000),id(counter + 1), currentPosition(0), name(name),bankrupt(false){
	ownedProperties = *(new std::vector<Tile*>);
	counter++;
	sprite = new Sprite(filepath,unitW,unitH,unitX,unitY);
	remainingSteps = 0;
	finishMoving = false;
	renderDelay = 300;
	lastRender = 0;
	flagType = DICE_MOVE;
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
void Player::setRemainingSteps(int remainingSteps) {
	this->remainingSteps = remainingSteps;
}
Sprite* Player::getSprite() {
	return sprite;
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
	return false;
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
/*
Asta se intampla doar cand playerul trebuie sa ajunga la Jail. O sa aibe cum ati zis voi 50 - currentPosition pozitii de mutat, iar cand termina de mutat,
remainingSteps == 0, atunci se initiaza goToJail
Totusi, in iteratiile Game::update() si Game::render() el figureaza ca mai are de mutat, deci il las sa mute. Flag-ul e pentru cand termina de mutat
*/

void Player::gotToJail() {
	std::cout << name << " will GO TO JAIL !\n";
		currentPosition = 10;
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

/*
Player's Sprite Position will be updated only agter a delay, set by renderDelay
and only if it has more than 0 steps to move. 
Otherwise player's sprite keeps its position
*/
void Player::update() {
	if (SDL_GetTicks() - lastRender >= renderDelay) {
		/*
		Daca NU e Jailed, i.e. e deja in tile-ul jail SI mai are pasi de facut, atunci pozitia lui se updateaza
		*/
		if (!isJailed() && remainingSteps > 0) {
			currentPosition++;
			if (currentPosition != currentPosition % 40)
			{
				std::cout << "Ai trecut de GO! Primesti 200 de BISTARI!" << std::endl;
				this->totalMoney += 200;
			}
			currentPosition %= 40;
			sprite->updateTo(coordX[currentPosition],coordY[currentPosition]);
			remainingSteps--;
			/*
			Cand nu mai are pasi de mutat, atunci, tot in Game::update() o sa arate ca urmeaza interactiunea cu tile[currentPositon]
			*/
			if (remainingSteps == 0)
				finishMoving = true;
			lastRender = SDL_GetTicks();
			std::cout << "player " << name << " has to move " << remainingSteps << " steps \n ";
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
