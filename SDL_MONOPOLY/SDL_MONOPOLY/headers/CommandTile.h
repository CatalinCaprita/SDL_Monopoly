#pragma once
#ifndef COMMANDTILE_H
#define COMMANDTILE_H
#include "Properties.h"
class CommandTile:public Tile {
public:
	CommandTile(const std::string& name);
	void doEffect(Player* currentPlayer);
	void print();
	std::string& getFrontTexturePath();
private:
	std::string backTexturePath;
	std::string frontTexturePath;
	Groups groupId;
	int destX, destY;
};
#endif // !COMMANDTILE_H
