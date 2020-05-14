#ifndef TILE_H
#define TILE_H
#include <string>
#include <iostream>
#include "SDL.h"
#include "Groups.h"
class Player;
class Tile{
protected:
	std::string name;
	std::string texturePath;
	Groups groupId;
public:
	Tile(std::string name,Groups groupId = RED);
	std::string getName();
	virtual void doEffect(Player* currentPlayer) = 0;
	virtual void getMeAnOwner(Player* currentPlayer) = 0;
	virtual void print() = 0;
	virtual void render(){}
	virtual bool isRenderable() {
		return false;
	}
	std::string& getTexturePath() {
		return texturePath;
	}
	Groups getGroupId() {
		return groupId;
	}
	
};
#endif // !TILE_H
