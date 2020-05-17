#include "../headers/Page.h"
Page::Page(Game* game, int xpos, int ypos) {
	this->game = game;
	test = new Button("assets/buy_button0.bmp", "assets/buy_button1.bmp", xpos, ypos, 22, 10);
	test->getSprite()->setScale(800, 1300);
}

void Page::listen_event() {
	int mouseX, mouseY;
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (test->hoverButton(mouseX, mouseY)) {
				int activePage = game->getMenu()->getCurrentPage();
				activePage++;
				activePage %= 2;
				game->getMenu()->setCurrentPage(activePage);
			}
	}
	
}

void Page::render() {
	test->render();
}