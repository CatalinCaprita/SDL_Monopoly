#pragma once
#ifndef COMMANDTILE_H
#define COMMANDTILE_H
#include "Properties.h"
#include <queue>
#include <vector>
#include <utility>
class CommandTile:public Tile {
public:
	CommandTile(const std::string& name);
	void doEffect(Player* currentPlayer);
	void getMeAnOwner(Player* currentPlayer);
	void mortgage(Player* currentPlayer);
	void print();
	std::string& getFrontTexturePath();
	static void shuffle(std::queue<int> &);
private:
	std::string backTexturePath;
	std::string frontTexturePath;
	static std::queue<int> chanceQ, communityQ;
	int destX, destY;
	static bool initialized;
};
#endif // !COMMANDTILE_H
