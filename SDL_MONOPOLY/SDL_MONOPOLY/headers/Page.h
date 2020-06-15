#pragma once
#include <vector>
#include "../headers/Button.h"
#include "../headers/Game.h"
#include "../headers/UILabel.h"

class Game;

class Page {
private:
	Player* player;
	Button* test;
	Game* game;
	UILabel* nameLabel;
	UILabel* moneyLabel;
	UILabel* mortgagedLabel;
	UILabel* notMortgagedLabel;
	std::vector<Tile*> playerOwnedProperties;
	std::vector<UILabel*> propertyLabelMortgaged;
	std::vector<UILabel*> propertyLabelNotMortgaged;
	int pageNumber;
public:
	Page(Game* game, Player* player);
	~Page();
	void update();
	void render();
	void listen_event();
};