#include "../headers/Menu.h"

Menu::Menu(Game* game) {
	this->game = game;
	int game_height = game->getScreenH();
	int game_width = game->getScreenW();
	/*int menu_height = game->getScreenH();
	int menu_width = 300;*/

	sprite = new Sprite("assets/menu/panel6.bmp", 31, 101, 99, 0);
	sprite->setScale(game_width, game_height);
	currentPage = 0;
	pages.push_back(new Page(game, 1));
	pages.push_back(new Page(game, 2));
	//pages.push_back(new Page(game, 3));
	//pages.push_back(new Page(game, 4));
}

void Menu::render() {
	sprite->render();
	pages[currentPage]->render();
}

void Menu::listen_event() {
	pages[currentPage]->listen_event();
}

void Menu::setCurrentPage(int page) {
	currentPage = page;
}

int Menu::getCurrentPage() {
	return currentPage;
}