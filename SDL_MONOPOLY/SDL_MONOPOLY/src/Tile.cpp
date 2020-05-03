#include "../headers/Tile.h"
#include "../headers/Player.h"
#include <string>

Tile::Tile(std::string name1) {
	name = name1;
}

std::string Tile ::getName() {
	return this->name;
}