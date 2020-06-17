#include "../headers/UserAnimator.h"
#include "../headers/TextureMaker.h"
#include <iostream>
#include <string>
#define CARD_START_POS_X 35
#define CARD_START_POS_Y 46
#define CARD_END_POS_X 15
#define CARD_END_POS_Y 26
//Defines used for the payerPaysPLayer
#define P1_END_X 25
#define P1_END_Y 36
#define P2_END_X 76
#define P2_END_Y 36
//Defines for the popUpMessage
#define MON_MAN_X 54
#define MON_MAN_Y 60
#define MAX_PROMPT_W 40
#define MAX_PROMPT_H 30
//Defines for the tradeTime
#define TRADEL_X 17
#define TRADEL_Y 58
#define TRADER_X 67
#define TRADER_Y 57
#define TRADE_MON_X 42
#define TRADE_MON_Y 21
#define TRADE_MONW 20
#define TRADE_MONH 34
#define TRADE_PX 16
#define TRADE_PY 27
#define TRADE_PW 40
#define TRADE_PH 30

Game* UserAnimator::game = NULL;
double UserAnimator::lastRender = 0.0;
int UserAnimator::renderDelay = 300;
std::unordered_map<std::string, Sprite*> UserAnimator::sprites;
std::vector<Prompt*> UserAnimator::prompts;
std::vector<Button*> UserAnimator::buttons;
//Variables used in trading
bool UserAnimator::buyerFlag = false;
bool UserAnimator::ownerFlag = false;
int pReached = 0;
TextBox* UserAnimator::textBox = nullptr;
Player* UserAnimator::buyerP = nullptr;
Player* UserAnimator::ownerP = nullptr;
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

} // Pops up a Tile on the screen
	
void UserAnimator::playerPaysPlayer(Player* src, Player* dest) {
	auto item = sprites.find("src");
	if (item != sprites.end())
		return;
	item = sprites.find("dest");
	if (item != sprites.end())
		return;

	Sprite* srcSprite = new Sprite(src->getSprite());
	srcSprite->setPath(src->getSprite()->getPath(),true);
	Sprite* destSprite = new Sprite(dest->getSprite());
	destSprite->setPath(dest->getSprite()->getPath(), true);
	destSprite->setRenderDelay(45);
	srcSprite->setRenderDelay(45);
	destSprite->updateUnitHeigth(10); destSprite->updateUnitWidth(10);
	srcSprite->updateUnitHeigth(10); srcSprite->updateUnitWidth(10);
	sprites.insert({ "src",srcSprite });
	sprites.insert({ "dest",destSprite });
	pReached = 0;

} // Animation where "src" pays "dest"

void UserAnimator::fadePropertyCard(Tile * target) {
	auto item = sprites.find("pop");
	if (item != sprites.end()) {
		sprites.insert({ "fade",sprites["pop"] });
		sprites.erase("pop");
		lastRender = 0; 
		
	}
} // Animation where the Tile on screen fades out

void UserAnimator::popUpMessage(std::string& message) {
	Prompt* prompt = new Prompt("assets/bubble_prompt.bmp", MON_MAN_X, MON_MAN_Y + 5, 0, 0,message);
	prompt->setScale(game->getScreenW(), game->getScreenH());
	prompt->setLifeTime(3000);
	prompts.push_back(prompt);
	auto it = sprites.find("mon_man");
	if (it == sprites.end()) {
		Sprite* monopolyMan = new Sprite("assets/monopoly_man.bmp", 10, 17, MON_MAN_X, MON_MAN_Y, game->getScreenW(), game->getScreenH(), true);
		sprites.insert({ "mon_man", monopolyMan });
		std::cout << "Inserted Mon_man";
	}
} // Animation where Monopoly Man appears and gives a prompt

/*Sets up the Trading process ,Loading Sprites*/
void UserAnimator::startTrade(Player * buyer, Player * owner) {
	buyer->startTrade(owner);
	buyer->setBuyerTradeFlag();
	owner->startTrade(buyer);
	owner->setOwnerTradeFlag();
	Sprite* buyerSprite = new Sprite(buyer->getSprite()->getPath(),10,12,TRADEL_X,TRADEL_Y,game->getScreenW(),game->getScreenH(),true);
	
	Sprite* ownerSprite = new Sprite(owner->getSprite()->getPath(), 10, 12, TRADER_X, TRADER_Y, game->getScreenW(), game->getScreenH(), true);
	
	Sprite* monOwner = new Sprite("assets/trade/trade_mon_own.bmp", TRADE_MONW, TRADE_MONH, TRADE_MON_X, TRADE_MON_Y, game->getScreenW(), game->getScreenH(), true);
	Sprite* monBuy = new Sprite("assets/trade/trade_mon_buy.bmp", TRADE_MONW, TRADE_MONH, TRADE_MON_X, TRADE_MON_Y, game->getScreenW(), game->getScreenH(), true);
	
	ownerSprite->setRenderDelay(45);
	buyerSprite->setRenderDelay(45);
	sprites.insert({ "buyer",buyerSprite });
	sprites.insert({ "owner",ownerSprite });
	sprites.insert({ "monBuyer",monBuy });
	sprites.insert({ "monOwner",monOwner});
	std::string m = "Enter the sum you propse to " + owner->getName();
	Prompt* buyPrompt = new Prompt("assets/trade/trade_bubble.bmp", TRADE_PX, TRADE_PY, TRADE_PW, TRADE_PH, m);
	buyPrompt->setSumInput(true);
	buyPrompt->setClickFadeable(false);
	buyPrompt->setTextWH(TRADE_PW * 0.75 , TRADE_PH * 0.35);
	buyPrompt->adjustText(-3,4,TRADE_PW);
	buyPrompt->setScale(game->getScreenW(), game->getScreenH());
	
	m = buyer->getName() + ", do you accept that much?";
	Prompt* ownPrompt = new Prompt("assets/trade/trade_bubble2.bmp", TRADE_MON_X + TRADE_MONW * 0.25, TRADE_PY, TRADE_PW, TRADE_PH, m);

	ownPrompt->setAcceptInput(true);
	ownPrompt->setClickFadeable(false);
	ownPrompt->setScale(game->getScreenW(), game->getScreenH());
	ownPrompt->setTextWH(TRADE_PW * 0.75, TRADE_PH * 0.35);
	ownPrompt->adjustText(0,4);
	prompts.push_back(buyPrompt);
	prompts.push_back(ownPrompt);
	std::string nullMess = " ";
	
	textBox = new TextBox("assets/trade/trade_text_box.bmp", TRADE_PX + 1, TRADE_PY + TRADE_PH * 0.75, TRADE_PW -5 , 5,nullMess);
	textBox->setScale(game->getScreenW(), game->getScreenH());
	SDL_SetTextInputRect(&textBox->getRect());
	buttons.push_back(new Button("assets/trade/yes_button.bmp", "assets/trade/yes_button.bmp", "assets/trade/yes_button.bmp",
		TRADE_MON_X + TRADE_MONW * 0.4, TRADE_PY + TRADE_PH * 0.75, 5, 5));
	buttons.push_back(new Button("assets/trade/no_button.bmp", "assets/trade/no_button.bmp", "assets/trade/no_button.bmp",
		TRADE_MON_X + TRADE_MONW * 0.75, TRADE_PY + TRADE_PH * 0.75, 5, 5));
	for(Button *b : buttons)
		b->getSprite()->setScale(game->getScreenW(), game->getScreenH());
	ownerP = owner;
	buyerP = buyer;
	buyerFlag = true;
	ownerFlag = false;


}
void UserAnimator::endTrade() {
	delete sprites["buyer"];
	sprites.erase("buyer");
	delete sprites["owner"];
	sprites.erase("owner");
	delete sprites["monBuyer"];
	sprites.erase("monBuyer");
	delete sprites["monOwner"];
	sprites.erase("monOwner");
	for (int i = buttons.size() - 1; i >= 0; i--) {
		delete buttons[i];
		buttons.erase(buttons.begin() + i);
	}
	for (int i = prompts.size() - 1; i >= 0; i--) {
		delete prompts[i];
		prompts.erase(prompts.begin() + i);
	}
	std::string endmsg = "Trade Finished!";
	popUpMessage(endmsg);

}
void UserAnimator::setBuyerFlag() {
	buyerFlag = true;
	ownerFlag = false;
}

void UserAnimator::setOwnerFlag() {
	buyerFlag = false;
	ownerFlag = true;
}
/*
Updates all the sprite components of the map according to the specification 
*/

void UserAnimator::update() {
	bool onFade = false;
	for (auto item = sprites.begin(); item != sprites.end();) {
		//IF there is a property deed sprite to be updated, update it accordingly
		if (item->first == "pop") {
			if (item->second->canBeUpdated()) {
				if (item->second->unitX() > CARD_END_POS_X&& item->second->unitY() > CARD_END_POS_Y) {
					item->second->updateUnitHeigth(2);
					item->second->updateUnitWidth(1);
					item->second->update(-1, -1);
					lastRender = SDL_GetTicks();

				}
				else if (item->second->isClicked()) {
					onFade = true;
				}
			}
			++item;
		}
		else if (item->first == "fade") {
			if (item->second->canBeUpdated()) {
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
					if (item == sprites.end())
						break;
				}
			}
		}
		else if (item->first == "src") {
			if (item->second->canBeUpdated()) {
				if (item->second->unitX() == P1_END_X && (item->second->unitY() == P1_END_Y)) {
					if (pReached < 2)
						pReached++;
					else {
						auto it = sprites.find("money");
						if (it == sprites.end()) {

							Sprite* moneySprite = new Sprite(item->second);
							moneySprite->setPath("assets/money_bag.bmp", true);
							moneySprite->setRenderDelay(65);
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
			if (item->second->canBeUpdated()) {
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
			if (item->second->canBeUpdated()) {
				if (item->second->unitX() < P2_END_X) {
					item->second->update(1, 0);

				}
				else {
					delete sprites["dest"];
					sprites.erase("dest");
					delete sprites["src"];
					sprites.erase("src");
					delete sprites["money"];
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
		else {
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
			else  if (prompts[i]->isClickFadeable() && prompts[i]->getBubbleSprite()->isClicked()) {
				std::cout << "Bubble clicked!";
				delete prompts[i];
				prompts.erase(prompts.begin() + i);
				std::cout << "Deleted sucessfully";
				delete sprites["mon_man"];
				sprites.erase("mon_man");

			}
		}
	}
	if (onFade)
		fadePropertyCard(nullptr);
	if (textBox != nullptr && buyerFlag) {
		textBox->update();
		if (textBox->isReturn()) {
			int sum = std::stoi(textBox->getInput());
			std::cout << "SUM :"<<sum<<" OwnerMoney : " << ownerP->getMoney() << "BuyerMoney : " << buyerP->getMoney();
			std::string message;
			if (sum < 0) {
				message = "You Can Only Trade with positive numbers!";
				popUpMessage(message);
			}
			else if (buyerP->getMoney() < sum) {
				message = "You Do Not Have the Money!";
				popUpMessage(message);
			}
			else {
				buyerP->proposeSum(sum);
			}

		}

	}
	if (ownerFlag && buttons.size() > 0) {
		for (Button* b : buttons) {
			b->update(Game::getMouseX(), Game::getMouseY());
		}
		if (buttons[0]->getSprite()->isClicked()) {
			//Owner Accepts the Sum
			ownerP->acceptOffer();
			endTrade();

		}
		else if (buttons[1]->getSprite()->isClicked()) {
			ownerP->denyOffer();
		}
	}
}

void UserAnimator::render() {
	for (auto it : sprites) {
		if (it.first == "monBuyer") {
			if (buyerFlag) {
				it.second->render();
			}
		}
		else if (it.first == "monOwner") {
			if (ownerFlag) {
				it.second->render();
			}
		}
		else {
			it.second->render();
		}
	}
	for (Prompt *p : prompts) {
		if (p->isSumImput()) {
			if(buyerFlag)
				p->render();
		}
		else if (p->isAcceptInput()) {
			if(ownerFlag)
				p->render();
		}
		else
			p->render();
	}
	if(textBox != nullptr && buyerFlag)
		textBox->render();
	if (ownerFlag && buttons.size() > 0) {
		for (Button* b : buttons) {
			b->render();
		}
	}
}