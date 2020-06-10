#include "../headers/Menu.h"

Menu::Menu(Game* game) {
	this->game = game;
	currentPage = 0;
	pages.push_back(new Page(game, 1));
	pages.push_back(new Page(game, 2));
	//pages.push_back(new Page(game, 3));
	//pages.push_back(new Page(game, 4));
}

void Menu::render() {
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