#ifndef TILE_H
#define TILE_H
#include <string>
#include <iostream>
class Player;
class Tile{
protected:
	std::string name;
	std::string texturePath;
public:
	Tile(std::string name);
	std::string getName();
	std::string getTexturePath() {
		return texturePath;
	}
	virtual void doEffect(Player* currentPlayer) = 0;
	virtual void print() = 0;

};
#endif // !TILE_H
