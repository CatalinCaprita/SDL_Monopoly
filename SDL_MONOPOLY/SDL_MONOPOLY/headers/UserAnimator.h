#ifndef USERANIMATOR_H
#define USERANIMATOR_H
#include "Tile.h"
#include "SDL.h"
#include "Game.h"
#include "Sprite.h"
class Tile;
class Player;
class UserAnimator {
public:
	static void popPropertyCard(Tile*);
	static void playerPaysPlayer(Player*, Player*);
	static void fadePropertyCard(Tile*);
	static void attach(Game *instance) {
		game = instance;
	}
	static void setDelay(int milliseconds);
private:
	UserAnimator();
	~UserAnimator();
	static Game* game;
	static SDL_Texture* backup;
	static Sprite* sprite;
	static double lastRender;
	static int renderDelay;
};
#endif // !USERANIMATOR_H
#pragma once
