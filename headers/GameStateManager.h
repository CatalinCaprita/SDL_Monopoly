#ifndef GAMESTATEMANAGER_H
#define GAMAESTATEMANAGER_H

#include "SDL.h"
#include <vector>
#include <iostream>
class GameState;
class GameStateManager {

public:
	static GameStateManager* getInstance() {
		if (instance == nullptr) {
			instance = new GameStateManager();
		}
		return instance;
	}
	~GameStateManager();
	void init(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen);
	 SDL_Renderer* getRenderer();
	void listen_event();
	void render();
	void update();
	void pushState(GameState* state);
	void popState();
	bool running();

	bool mouseClick() {
		return mousePressed;
	}
	void setMousePressed(bool value) {
		mousePressed = value;
	}
	 int getClickX() {
		return clickX;
	};
	int getClickY() {
		return clickY;
	}

	void setClickX(int cx) {
		clickX = cx;
	};
	void  setClickY(int cy ) {
		clickY = cy;
	}
	int getMouseX() {
		return clickX;
	};
	int getMouseY() {
		return clickY;
	}
	bool isStroke() {
		return keyStroke;
	}
	void setKeyStroke(bool value) {
		keyStroke = value;
	}
	char getInChar() {
		return inChar;
	}
	void setInChar(char c) {
		inChar = c;
	}
	bool isBack() {
		return backPressed;
	}
	void setBackFlag(bool value) {
		backPressed = value;
	}
	bool isEnter() {
		return enterPressed;
	}
	void setEnterFlag(bool value) {
		enterPressed = value;
	}
	void setRenderer(SDL_Renderer* rend) {
		renderer = rend;
	}


private:
	static GameStateManager* instance;
	std::vector<GameState* >states;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateManager();
	bool keyStroke;
	bool backPressed;
	bool enterPressed;
	char  inChar;
	int mouseX;
	int mouseY;
	int clickX;
	int clickY;
	bool mousePressed;


};
#endif // !GAMESTATEMANAGER_H
#pragma once
