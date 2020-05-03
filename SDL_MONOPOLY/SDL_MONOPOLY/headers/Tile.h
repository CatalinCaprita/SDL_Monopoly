#ifndef TILE_H
#define TILE_H
#include <string>
#include <iostream>
class Player;
class Tile{
protected:
	std::string name;
public:
	Tile(std::string name);
	std::string getName();
	virtual void doEffect(Player* currentPlayer) = 0;
	virtual void print() = 0;
};
#endif // !TILE_H
