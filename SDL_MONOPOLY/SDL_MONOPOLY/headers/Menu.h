#pragma once
#include "../headers/Page.h"
#include "../headers/Game.h"

class Game;
class Page;

class Menu {
private:
	std::vector<Page*> pages;
	int currentPage;
	Sprite* sprite;
	Game* game;
public:
	Menu(Game* );
	~Menu();
	void render();
	void listen_event();
	void setCurrentPage(int);
	int getCurrentPage();
};