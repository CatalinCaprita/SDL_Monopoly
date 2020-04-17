#include "../headers/Player.h"
#include "../headers/Tile.h"
#include <string>
#include <iostream>
int Player::counter = 0;
Player::Player(std::vector<Tile*>&t,std::string name) :totalMoney(10000),id(counter + 1),tiles(t),name(name){
	counter++;
}
Player::~Player() {

}
void Player::move() {
	tiles[1]->doEffect(this);
}

int Player::recieveMoney(int amount) {
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
std::string& Player::getName() {
	return name;
}
