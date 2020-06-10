#pragma once
#include <vector>
#include "../headers/Button.h"
#include "../headers/Game.h"
#include "../headers/UILabel.h"

class Game;

class Page {
private:
	Button* test;
	Game* game;
	UILabel* nameLabel;
	UILabel* moneyLabel;
	int pageNumber;
public:
	Page(Game*, int);
	~Page();
	void update();
	void render();
	void listen_event();
};