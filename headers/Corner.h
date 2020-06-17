#pragma once
#ifndef CORNER_H
#define CORNER_H
#include "Properties.h"
#include "Tile.h"
#include "Player.h"
#include "Groups.h"
class Tile;
class Corner : public Tile {
public :
	Corner(std::string& name,std::string& command,int cornerNo);
	~Corner();
	std::string getName() {
		return name;
	}
	void doEffect(Player* currentPlayer);
	void getMeAnOwner(Player* currentPlayer);
	void mortgage(Player* currentPlayer);
	void print() {
		std::cout << command << std::endl;
	}
private :
	std::string command;
	int cornerNo;
};
#endif // !CORNER_H
