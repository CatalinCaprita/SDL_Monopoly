#ifndef USERANIMATOR_H
#define USERANIMATOR_H
#include "Tile.h"
#include "SDL.h"
#include "Game.h"
#include "Sprite.h"
#include "Properties.h"
#include "Prompt.h"
class Tile;
class Player;
class UserAnimator {
public:
	static void popPropertyCard(Tile*);
	static void playerPaysPlayer(Player*, Player*);
	static void fadePropertyCard(Tile*);
	static void popCommandCardBack(CommandTile* card);
	static void popUpMessage(std::string & message);
	static void update();
	static void render();
	static void attach(Game *instance) {
		game = instance;
	}
	static void setDelay(int milliseconds);
private:
	UserAnimator();
	~UserAnimator();
	static Game* game;
	static SDL_Texture* backup;
	static std::unordered_map<std::string,Sprite*> sprites;
	static std::vector<Prompt*> prompts;
	static double lastRender;
	static int renderDelay;
};
#endif // !USERANIMATOR_H
#pragma once
