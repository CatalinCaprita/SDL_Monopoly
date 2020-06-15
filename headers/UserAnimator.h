#ifndef USERANIMATOR_H
#define USERANIMATOR_H
#include "Tile.h"
#include "SDL.h"
#include "Game.h"
#include "Sprite.h"
#include "Properties.h"
#include "Prompt.h"
#include "TextBox.h"
class Tile;
class Player;
class UserAnimator {
public:
	static void popPropertyCard(Tile*);
	static void playerPaysPlayer(Player*, Player*);
	static void fadePropertyCard(Tile*);
	static void popCommandCardBack(CommandTile* card);
	static void popUpMessage(std::string& message);
	static void update();
	static void render();
	static void attach(Game *instance) {
		game = instance;
	}
	static void setDelay(int milliseconds);
	static void startTrade(Player *buyer, Player *owner);
	static void endTrade();
	static void setOwnerFlag ();
	static void setBuyerFlag();
private:
	UserAnimator();
	~UserAnimator();
	static Game* game;
	static SDL_Texture* backup;
	static std::unordered_map<std::string,Sprite*> sprites;
	static std::vector<Prompt* >prompts;
	static std::vector<Button* >buttons;
	static double lastRender;
	static bool tradeOn;
	static int renderDelay;
	static bool buyerFlag;
	static bool ownerFlag;
	static TextBox *textBox;
	static Player* buyerP, *ownerP; //Since there can only be at most ONE TRADE Session at a time.
};
#endif // !USERANIMATOR_H
#pragma once
