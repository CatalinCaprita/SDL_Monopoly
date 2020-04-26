#ifndef TILE_H
#define TILE_H
#include <string>
#include <iostream>
#include "SDL.h"
class Player;
class Tile{
protected:
	std::string name;
	std::string texturePath;
public:
	Tile(std::string name);
	std::string getName();
	virtual void doEffect(Player* currentPlayer) = 0;
	virtual void print() = 0;
	std::string& getTexturePath() {
		return texturePath;
	}
};
#endif // !TILE_H
