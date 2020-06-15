#include "../headers/Page.h"
#include <string>
#include "../headers/Prompt.h"

Page::Page(Game* game, Player* player) {
	this->game = game;
	this->player = player;

	std::string text = player->getName();// game->getPlayer(i - 1)->getName();
	if(text.length() <= 8)
		nameLabel = new UILabel(102, 20, 3 * text.length(), 8, text, TTF_OpenFont("assets/fonts/lucida_sans.ttf", 60), *(new SDL_Color({0,0,0,0})));
	else
		nameLabel = new UILabel(102, 20, 24, 8, text, TTF_OpenFont("assets/fonts/lucida_sans.ttf", 60), *(new SDL_Color({ 0,0,0,0 })));

	nameLabel->setLabelTexture(game->getScreenW());
	nameLabel->setScale(game->getScreenW(), game->getScreenH());

	std::string money = ( "$" + std::to_string(player->getMoney()) );
	moneyLabel = new UILabel(102, 27, 18, 8, money, TTF_OpenFont("assets/fonts/lucida_sans.ttf", 60), *(new SDL_Color({ 0,0,0,0 })));
	moneyLabel->setLabelTexture(game->getScreenW());
	moneyLabel->setScale(game->getScreenW(), game->getScreenH());

	
}

void Page::listen_event() {
}

void Page::render() {
	//DEBUG
	playerOwnedProperties = player->getOwnedProperties();
	UILabel* label = NULL;
	for (int i = 0; i < playerOwnedProperties.size(); i++)
	{
		std::string text = playerOwnedProperties[i]->getName();
		label = new UILabel(102, 27 + i*2, 18, 3, text, TTF_OpenFont("assets/fonts/lucida_sans.ttf", 60), *(new SDL_Color({ 0,0,0,0 })) );
		label->setLabelTexture(this->game->getScreenW());
		label->setScale(this->game->getScreenW(), this->game->getScreenW());
		if (propertyLabelNotMortgaged.size() < 1)
			propertyLabelNotMortgaged.push_back(label);
		else
			propertyLabelNotMortgaged[0] = label;

		propertyLabelNotMortgaged[0]->render();
		delete label;
	}
	//
	/*for (int i = 0; i < propertyLabelNotMortgaged.size(); i++) {
		if (propertyLabelNotMortgaged[i] != NULL) {
			propertyLabelNotMortgaged[i]->render();
		}

	}*/
	nameLabel->render();
	moneyLabel->render();
}
void Page::update(){
	std::string money = ( "$" + std::to_string(player->getMoney()) );
	moneyLabel->setMessage(money);
	moneyLabel->setLabelTexture(game->getScreenW());
}