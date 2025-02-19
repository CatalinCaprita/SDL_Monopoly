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
#include "GameState.h"

class Menu;

class Game: public GameState {
public:
	friend class Player;
	Game(int width, int height, std::vector<std::string> &playerNames);
	~Game();
	bool running() {
		return isRunning;
	}
	void update();
	void render();
	void listen_event();
	void fillTiles(const char *);

	Menu* getMenu();
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
	};
	static int getMouseX() {
		return clickX;
	};
	static int getMouseY() {
		return clickY;
	}
	static bool isStroke() {
		return keyStroke;
	}
	static void setKeyStroke(bool value) {
		keyStroke = value;
	}
	static char getInChar() {
		return inChar;
	}
	static bool isBack() {
		return backPressed;
	}
	static void setBackFlag(bool value) {
		backPressed = value;
	}
	static bool isEnter() {
		return enterPressed;
	}
	static void setEnterFlag(bool value) {
		enterPressed = value;
	}
	static void setRenderer(SDL_Renderer* rend) {
		renderer = rend;
	}
	std::vector<Player*> getPlayers() {
		return players;

	}
	Player* getPlayer(int i) {
		return players[i];
	}

	
private:
	int findPlayer(std::string);
	bool doesPlayerExist(std::string);
	int turn;
	int screenWidth, screenHeight;
	static int count;
	static int nrDoublesThrown;

	/*Click-related variables*/
	static bool buyPressed;
	static bool mortgagePressed;
	static int mouseX;
	static int mouseY;
	static int clickX;
	static int clickY;
	static bool mousePressed;

	/*GUI Related variables*/
	bool isRunning;
	static bool keyStroke;
	static bool backPressed;
	static bool enterPressed;
	static char  inChar;
	UILabel* currentPlayerLabel;
	Sprite* currentPlayerSprite;
	std::vector<Player*> players;
	std::vector<Button*> buttons;
	std::vector<Button*> playerPageButtons;
	static Dice* dice;
	SDL_Window* window;			//window object to be used as the main game frame
	static SDL_Renderer* renderer;		//renderer composite passed as arg to all render functinos. see update() and render()
	Sprite* background;
	std::vector<Tile*> tiles;
	Prompt* test_prompt;
	Menu* menu;
	
};
#endif // !GAME_H