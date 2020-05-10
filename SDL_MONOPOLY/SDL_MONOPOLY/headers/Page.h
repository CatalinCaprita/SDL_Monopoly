#pragma once
#include <vector>
#include "../headers/Button.h"
#include "../headers/Game.h"

class Game;

class Page {
private:
	Button* test;
	Game* game;
public:
	Page(Game*, int, int);
	~Page();
	void update();
	void render();
	void listen_event();
};