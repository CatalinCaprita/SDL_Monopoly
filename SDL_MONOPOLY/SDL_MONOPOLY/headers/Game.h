#ifndef GAME_H
#define GAME_H
#pragma once
#include <iostream>
#include "SDL.h"
#include "../headers/Tile.h"
#include "../headers/Dice.h"
#include "../headers/Button.h"
#include <vector>
#include "../headers/Player.h"
#include "../headers/Tile.h"
#include "../headers/HouseProperty.h"
#include "../headers/Groups.h"

class Game {
public:
	friend class Player;
	Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen);
	~Game();
	bool running() {
		return isRunning;
	}
	void update();
	void render();
	void listen_event();
	void fillTiles(const char *);
private:
	int turn;
	static int count;
	bool isRunning;
	bool mousePressed;
	static int nrDoublesThrown;
	std::vector<Player*> players;
	std::vector<Button*> buttons;
	Dice* dice;
	SDL_Window* window;			//window object to be used as the main game frame
	SDL_Renderer* renderer;		//renderer composite passed as arg to all render functinos. see update() and render()
	SDL_Rect spriteFrame;		//experimented a little :)) So far just to set the size of a pawn
	SDL_Texture* playerTexture;		//Texture that representes a player's Pawn. Soon to be integrated in the Player - related Class
	SDL_Texture* background;		//Texture to fill the window frame
	std::vector<Tile*> tiles;

};
#endif // !GAME_H
