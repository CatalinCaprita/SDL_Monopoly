#include "../headers/Menu.h"

Menu::Menu(Game* game) {
	this->game = game;
	currentPage = 0;
	pages.push_back(new Page(game,10,10));
	pages.push_back(new Page(game,20,20));
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