#include "../headers/Player.h"
#define OFFSET 2
int Player::counter = 0;
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

Player::Player(std::vector<Tile*>& t, std::string name, const char* filepath, int xpos, int ypos, int height, int width) : totalMoney(10000),id(counter + 1), currentPosition(0), ownedProperties(t), name(name), jailed(false),bankrupt(false){
	counter++;
	spriteFrame.x = xpos;
	spriteFrame.y = ypos;
	spriteFrame.h = height;
	spriteFrame.w = width;
	playerTexture = TextureMaker::textureFromBMP(filepath);
}

Player::~Player() {
	/*
		TO DO
	*/
}

void Player::move(int value) {
	currentPosition += value;
	currentPosition %= 40;
	/* 
		call of tiles[position??].doEffect(this);
	*/
	SDL_Delay(200);
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

void Player::buyProperty(Tile* property)
{
	if (totalMoney < ((AbstractProperty*)property)->getRentPrice()) // needs testing
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

bool Player::isJailed()
{
	return jailed;
}

bool Player::isBankrupt()
{
	return bankrupt;
}

void Player::update() {
	spriteFrame.x = coordX[currentPosition] + (id - OFFSET) * 10;
	spriteFrame.y = coordY[currentPosition];
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, playerTexture, NULL, &spriteFrame);
}

void Player::print(){
	std::cout << "name: " << name << "id: " << id << "balance: " << totalMoney << "owned properties: ";
	for (auto x : ownedProperties)
		std::cout << x->getName() + "; ";
}