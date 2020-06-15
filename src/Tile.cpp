#include "../headers/Tile.h"
#include "../headers/Player.h"
#include <string>

Tile::Tile(std::string name,Groups groupId) {
	this->name = name;
	this->groupId = groupId;
}

std::string Tile ::getName() {
	return this->name;
}