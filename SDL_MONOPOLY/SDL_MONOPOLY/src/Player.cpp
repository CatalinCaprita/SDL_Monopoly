#include "../headers/Player.h"
#define OFFSET 3
int Player::counter = 0;
<<<<<<< HEAD
int coordX[] = { 950, 820, 738, 656, 574, 492, 410, 328, 246, 164, 20,
				 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				 164, 246, 328, 410, 492, 574, 656, 738, 820, 950,			// first substraction: 130;		every substraction after: 82;
				 940, 940, 940, 940, 940, 940, 940, 940, 940, 940,
=======

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
>>>>>>> alone_dev
				};
int coordY[] = { 91, 91, 91, 91, 91,  91, 91, 91, 91, 91,
				 92, 84, 74, 66, 58, 50, 42, 34, 26, 18,
				 6, 4, 4, 4, 4, 4, 4, 4, 4, 4,
				6, 16, 24, 32, 40, 48, 56, 64, 72, 80
				};

<<<<<<< HEAD
Player::Player(std::string name, const char* filepath, int xpos, int ypos, int height, int width) : totalMoney(10000),id(counter + 1), currentPosition(0), name(name),jailTurnsLeft(0),bankrupt(false){
	ownedProperties = *(new std::vector<Tile*>);
	counter++;
	spriteFrame.x = xpos;
	spriteFrame.y = ypos;
	spriteFrame.h = height;
	spriteFrame.w = width;
	playerTexture = TextureMaker::textureFromBMP(filepath);
=======
//W, H, X, Y  will be in GAME_UNITS now, see Game.cpp and Sprite.h
Player::Player(std::string name, const char* filepath, int unitX, int unitY, int unitH, int unitW) : totalMoney(10000),id(counter + 1), currentPosition(0), name(name),bankrupt(false){
	ownedProperties = *(new std::vector<Tile*>);
	counter++;
	sprite = new Sprite(filepath,unitW,unitH,unitX,unitY);
	remainingSteps = 0;
	finishMoving = false;
	renderDelay = 300;
	lastRender = 0;
	mustBeJailed = false;
>>>>>>> alone_dev
}

Player::~Player() {
	/*
		TO DO
	*/
}

void Player::move() {
<<<<<<< HEAD
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

=======
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
>>>>>>> alone_dev
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

int Player::getCurrPosition()
{
	return currentPosition;
}

bool Player::isJailed()
{
	return !(jailTurnsLeft == 0);
}
<<<<<<< HEAD

void Player::goToJail()
{
	currentPosition = 10;
	jailTurnsLeft = 3;
=======
/*
Asta se intampla doar cand playerul trebuie sa ajunga la Jail. O sa aibe cum ati zis voi 50 - currentPosition pozitii de mutat, iar cand termina de mutat,
remainingSteps == 0, atunci se initiaza goToJail
Totusi, in iteratiile Game::update() si Game::render() el figureaza ca mai are de mutat, deci il las sa mute. Flag-ul e pentru cand termina de mutat
*/
void Player::setJailFlag() {
	mustBeJailed = true;
	std::cout << name << "Will be JAILED!\n";
}
void Player::gotToJail() {
		currentPosition = 10;
		jailTurnsLeft = 3;
>>>>>>> alone_dev
}

void Player::freeFromJail()
{
	jailTurnsLeft = 0;
}

void Player::setJailTurnsLeft(int turns)
{
	jailTurnsLeft = turns;
}

int Player::getJailTurnsLeft()
{
<<<<<<< HEAD
=======
	return !(jailTurnsLeft == 0);
}

void Player::freeFromJail()
{
	jailTurnsLeft = 0;
	mustBeJailed = false;
}

void Player::setJailTurnsLeft(int turns)
{
	jailTurnsLeft = turns;
	std::cout << name << " will be out of the game for the next " << turns << std::endl;
}

int Player::getJailTurnsLeft()
{
>>>>>>> alone_dev
	return jailTurnsLeft;
}

std::string& Player::getName() {
	return name;
}

bool Player::isBankrupt()
{
	return bankrupt;
}

void Player::update() {
<<<<<<< HEAD
	if (this->isJailed()) {
		spriteFrame.x = coordX[10] + (id - OFFSET) * 10 + 60;
		spriteFrame.y = coordY[10] - 55;
	}
	else {
		spriteFrame.x = coordX[currentPosition] + (id - OFFSET) * 10;
		spriteFrame.y = coordY[currentPosition];
=======
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
		/*
		Ori e in Jail deja, ori dupa ce muta trebuie sa ramana in Jail
		Aici ajung doar daca :
		- a terminat de mutat, remaningSteps == 0 , deci verificam daca dupa ce termina de mutat trebuia sa ajunga in Jail
		- e jailed, caz in care mustBeJailed e fals, ca deja e in Jail, deci o sa stea pe loc, adica update(0,0)
		finishMoving ramane fals, ca sa nu interactioneze cu tile[currentPosition]
		*/
		else {

			if (mustBeJailed)
				gotToJail();
			sprite->update(0, 0);
			finishMoving = false;
		}
>>>>>>> alone_dev
	}
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, playerTexture, NULL, &spriteFrame);
}

void Player::print(){
	std::cout << "name: " << name << "id: " << id << "balance: " << totalMoney << "owned properties: ";
	for (auto x : ownedProperties)
		std::cout << x->getName() + "; ";
}
