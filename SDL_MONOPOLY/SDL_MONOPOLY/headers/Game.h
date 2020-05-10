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
#include "../headers/Properties.h"
#include "../headers/Sprite.h"
#include "../headers/Menu.h"

class Menu;

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

	Menu* getMenu();
	bool getMousePressed();
	int getScreenW();
	int getScreenH();
	SDL_Window* getWindow();
	static Dice* getDice();
	static SDL_Renderer* getRenderer();
	static void createRenderer();
	
private:
	int turn;
	int screenWidth, screenHeight;
	static int count;
	static int nrDoublesThrown;
	bool isRunning;
	bool mousePressed;
	std::vector<Player*> players;
	std::vector<Button*> buttons;
	static Dice* dice;
	SDL_Window* window;			//window object to be used as the main game frame
	static SDL_Renderer* renderer;		//renderer composite passed as arg to all render functinos. see update() and render()
	Sprite* background;
	std::vector<Tile*> tiles;
	Menu* menu;

};
#endif // !GAME_H
