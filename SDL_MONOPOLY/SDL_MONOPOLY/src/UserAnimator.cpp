#include "../headers/UserAnimator.h"
#include "../headers/TextureMaker.h"
#include <iostream>
#include <string>
#define CARD_START_POS_X 35
#define CARD_START_POS_Y 46
#define CARD_END_POS_X 15
#define CARD_END_POS_Y 26
#define P1_END_X 25
#define P1_END_Y 36
#define P2_END_X 76
#define P2_END_Y 36
#define MON_MAN_X 54
#define MON_MAN_Y 60
#define MAX_PROMPT_W 40
#define MAX_PROMPT_H 30
Game* UserAnimator::game = NULL;
double UserAnimator::lastRender = 0.0;
int UserAnimator::renderDelay = 300;
std::unordered_map<std::string, Sprite*> UserAnimator::sprites;
std::vector<Prompt*> UserAnimator::prompts;

int pReached = 0;
UserAnimator::UserAnimator(){}

UserAnimator::~UserAnimator() {
	
}

void UserAnimator::setDelay(int milliseconds) {
	renderDelay = milliseconds;
}
void UserAnimator::popPropertyCard(Tile * target) {
	auto item = sprites.find("pop");
	if (item == sprites.end()) {
		std::string dest = target->getTexturePath();
		Sprite* sprite = new Sprite(dest.c_str(), 0, 0, CARD_START_POS_X, CARD_START_POS_Y, game->getScreenW(), game->getScreenH());
		sprite->setRenderDelay(20);
		renderDelay = 30;
		sprites.insert({ "pop",sprite });
		lastRender = 0;
		std::cout << "Successively inserted" << target->getName() << std::endl;
	}

}
	
void UserAnimator::playerPaysPlayer(Player* src, Player* dest) {
	auto item = sprites.find("src");
	if (item != sprites.end())
		return;
	item = sprites.find("dest");
	if (item != sprites.end())
		return;

	Sprite* srcSprite = new Sprite(src->getSprite());
	Sprite* destSprite = new Sprite(dest->getSprite());
	destSprite->setRenderDelay(45);
	srcSprite->setRenderDelay(45);
	destSprite->updateUnitHeigth(10); destSprite->updateUnitWidth(10);
	srcSprite->updateUnitHeigth(10); srcSprite->updateUnitWidth(10);
	sprites.insert({ "src",srcSprite });
	sprites.insert({ "dest",destSprite });
	pReached = 0;

}
void UserAnimator::fadePropertyCard(Tile * target) {
	auto item = sprites.find("pop");
	if (item != sprites.end()) {
		sprites.insert({ "fade",sprites["pop"] });
		sprites.erase("pop");
		lastRender = 0; 
		
	}
}

void UserAnimator::popUpMessage(std::string& message) {
	Prompt* prompt = new Prompt("assets/bubble_prompt.bmp", MON_MAN_X, MON_MAN_Y + 5, 0, 0, message);
	prompt->setScale(game->getScreenW(), game->getScreenH());
	prompt->setLifeTime(3000);
	prompts.push_back(prompt);
	auto it = sprites.find("mon_man");
	if (it == sprites.end()) {
		Sprite* monopolyMan = new Sprite("assets/monopoly_man.bmp", 10, 17, MON_MAN_X, MON_MAN_Y, game->getScreenW(), game->getScreenH(), true);
		sprites.insert({ "mon_man",monopolyMan });
		std::cout << "Insertet Mon_man";
	}
}
/*
Updates all the sprite components of the map according to the specification 
*/
void UserAnimator::update() {
	if (sprites.size() <= 0)
		return;
	
	for (auto item = sprites.begin(); item != sprites.end();) {
		//IF there is a property deed sprite to be updated, update it accordingly
		if (item->first == "pop") {
			if (item->second->candBeUpdated()) {
				if (item->second->unitX() > CARD_END_POS_X&& item->second->unitY() > CARD_END_POS_Y) {
					item->second->updateUnitHeigth(2);
					item->second->updateUnitWidth(1);
					item->second->update(-1, -1);
					lastRender = SDL_GetTicks();

				}
			}
			++item;
		}
		else if (item->first == "fade") {
			if (item->second->candBeUpdated()) {
				if (item->second->unitH() > 0 && item->second->unitW() > 0) {
	
					item->second->updateUnitHeigth(-2);
					item->second->updateUnitWidth(-1);
					item->second->update(1, 1);
					lastRender = SDL_GetTicks();
					++item;
				}
				else {
					delete item->second;
					item = sprites.erase(item);
					if(item == sprites.end())
						break;
				}
			}
		}
		else if (item->first == "src") {
			if (item->second->candBeUpdated()) {
				if (item->second->unitX() == P1_END_X && (item->second->unitY() == P1_END_Y)) {
					if (pReached < 2)
						pReached++;
					else {
						auto it = sprites.find("money");
						if (it == sprites.end()) {
							
							Sprite* moneySprite = new Sprite(item->second);
							moneySprite->setPath("assets/money_bag.bmp",true);
							moneySprite->setRenderDelay(65);
							std::cout << "Src triggered money beginning \n ";
							sprites.insert({ "money",moneySprite });
							break;
						}
						
					}
				}
				else {
					if (item->second->unitX() < P1_END_X) {
						item->second->update(1, 0);
					}
					else if (item->second->unitX() > P1_END_X) {
						item->second->update(-1, 0);
					}
					if (item->second->unitY() < P1_END_Y) {
						item->second->update(0, 1);
					}
					else if (item->second->unitY() > P1_END_Y) {
						item->second->update(0, -1);
					}
				}
			}
			++item;
		}
		else if (item->first == "dest") {
			if (item->second->candBeUpdated()) {
				if (item->second->unitX() == P2_END_X && (item->second->unitY() == P2_END_Y)) {
					if (pReached < 2)
						pReached++;	

				}
				else {
					if (item->second->unitX() < P2_END_X) {
						item->second->update(1, 0);
					}
					else if (item->second->unitX() > P2_END_X) {
						item->second->update(-1, 0);
					}
					if (item->second->unitY() < P2_END_Y) {
						item->second->update(0, 1);
					}
					else if (item->second->unitY() > P2_END_Y) {
						item->second->update(0, -1);
					}
				}
			}
			++item;
		}
		else if (item->first == "money") {
			if(item->second->candBeUpdated()){
				if (item->second->unitX() < P2_END_X) {
						item->second->update(1, 0);
					
				}
				else {
					sprites.erase("dest");
					sprites.erase("src");
					sprites.erase("money");
					break;
				}
			}
			++item;
		}
		else if (item->first == "mon_man") {
			item->second->update(0, 0);
			++item;
		}

	}	

	for (int i = 0; i < prompts.size(); i++) {
		if (prompts[i]->canBeUpdated()) {
			if (prompts[i]->getW() < MAX_PROMPT_W) {
				prompts[i]->updateWH(1);
			}
			if (prompts[i]->getH() < MAX_PROMPT_H) {
				prompts[i]->updateXY(0, -1);
				prompts[i]->updateWH(0, 1);
			}
			/*
			else {
				prompts[i]->decreaseLifeTime();
				if (prompts[i]->isDone()) {
					prompts.erase(prompts.begin() + i);
					break;
				}
			}*/
		}
	}
	
}

void UserAnimator::render() {
	for (auto it : sprites) {
		it.second->render();
	}
	for (auto it : prompts)
		it->render();
}