#ifndef STARTUP_H
#define STARTUP_H
#include "SDL.h"
#include <iostream>
#include "GameState.h"
#include "Sprite.h"
#include "UILabel.h"
#include "TextBox.h"
#include "Prompt.h"

class StartUpState : public GameState {
public:
	StartUpState(int screenW, int screenH);
	~StartUpState();
	void listen_event();
	void update();
	void render();
	bool running();
private:
	SDL_Renderer* renderer;
	Sprite* background;
	Sprite* monMan;
	Sprite* bubble;
	std::vector<UILabel*>labels;
	std::vector<TextBox*>tbs;
	std::vector<Button*> buttons;
	bool isRunning;

};
#endif // !STARTUP_H

#pragma once
