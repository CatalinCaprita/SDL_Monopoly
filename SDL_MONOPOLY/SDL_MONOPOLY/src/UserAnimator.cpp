#include "../headers/UserAnimator.h"
#include "../headers/TextureMaker.h"
#include <iostream>
#include <string>
#define CARD_START_POS_X 35
#define CARD_START_POS_Y 46
#define CARD_END_POS_X 15
#define CARD_END_POS_Y 26
Game* UserAnimator::game = NULL;
Sprite* UserAnimator::sprite = NULL;
double UserAnimator::lastRender = 0.0;
int UserAnimator::renderDelay = 0;
UserAnimator::UserAnimator(){}

UserAnimator::~UserAnimator() {}

void UserAnimator::setDelay(int milliseconds) {
	renderDelay = milliseconds;
}
void UserAnimator::popPropertyCard(Tile * target) {
	std::string dest = target->getTexturePath();
	sprite = new Sprite(dest.c_str(),0,0,CARD_START_POS_X,CARD_START_POS_Y,game->getScreenW(),game->getScreenH());
	renderDelay = 30;
	lastRender = SDL_GetTicks();
	int iterations = 0;
	int targetIterations = 20;
	while (iterations < targetIterations) {
		if (SDL_GetTicks() - lastRender >= renderDelay) {
			sprite->updateUnitHeigth(2);
			sprite->updateUnitWidth(1);
			sprite->update(-1, -1);
			game->render();
			sprite->render();
			SDL_RenderPresent(game->getRenderer());
			lastRender = SDL_GetTicks();
			iterations++;
		}
	}
	delete sprite;
	
}
void UserAnimator::playerPaysPlayer(Player* src, Player* dest) {
	Sprite* srcSprite = new Sprite(src->getSprite());
	Sprite* destSprite = new Sprite(dest->getSprite());
	int screenW = game->getScreenW();
	int screenH = game->getScreenH();
	Sprite* moneySprite = new Sprite("assets/money_bag.bmp", 3, 3, 0, 0, screenW, screenH);
	srcSprite->setPixelXY(screenW * 1 / 3, screenH * 1 / 3);
	destSprite->setPixelXY(screenW * 2 / 3, screenH * 1 / 3);
	moneySprite->setPixelXY(screenW * 1 / 3 + 20, screenH * 1 / 3 + 20);
	srcSprite->updateUnitHeigth(10);
	srcSprite->updateUnitWidth(10);
	destSprite->updateUnitHeigth(10);
	destSprite->updateUnitWidth(10);

	for (int i = 0; i < 1000; i++) {
		moneySprite->update(1, 0);
		game->render();
		srcSprite->render();
		moneySprite->render();
		destSprite->render();
		SDL_RenderPresent(game->getRenderer());
		SDL_Delay(10);
	}
}
void UserAnimator::fadePropertyCard(Tile * target) {
	std::string dest = target->getTexturePath();
	sprite = new Sprite(dest.c_str(),20,40,CARD_START_POS_X,CARD_START_POS_Y, game->getScreenW(), game->getScreenH());
	renderDelay = 80;
	lastRender = SDL_GetTicks();
	int iterations = 0;
	int targetIterations = 20;
	while (iterations < targetIterations) {
		if ((SDL_GetTicks() - lastRender) >= renderDelay) {
			std::cout << "Render Time  :" << SDL_GetTicks() - lastRender<< std::endl;
			sprite->updateUnitHeigth(-2);
			sprite->updateUnitWidth(-1);
			sprite->update(1,1);
			game->render();
			sprite->render();
			SDL_RenderPresent(game->getRenderer());
			lastRender = SDL_GetTicks();
			iterations++;
		}
	}
	delete sprite;
}



