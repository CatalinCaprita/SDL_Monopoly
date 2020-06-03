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
#include "../headers/UILabel.h"
#include "../headers/Prompt.h"
#include "SDL_ttf.h"

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
	static bool isBuyPressed() { return buyPressed; }
	static void setBuyPressed(bool buyPressed) { Game::buyPressed = buyPressed; }
	static bool isMortgagePressed() { return mortgagePressed; }
	static void setMortgagePressed(bool mortgagePressed) { Game::mortgagePressed = mortgagePressed; }
	static bool mouseClick() {
		return mousePressed;
	};
	static int getClickX() {
		return clickX;
	};
	static int getClickY() {
		return clickY;
	}
	
private:
	int turn;
	int screenWidth, screenHeight;
	static int count;
	static int nrDoublesThrown;
	static bool buyPressed;
	static bool mortgagePressed;
	static int mouseX;
	static int mouseY;
	static int clickX;
	static int clickY;
	static bool mousePressed;
	bool isRunning;
	std::vector<Player*> players;
	std::vector<Button*> buttons;
	static Dice* dice;
	SDL_Window* window;			//window object to be used as the main game frame
	static SDL_Renderer* renderer;		//renderer composite passed as arg to all render functinos. see update() and render()
	Sprite* background;
	std::vector<Tile*> tiles;
	Prompt* test_prompt;
	Menu* menu;

};
#endif // !GAME_H
