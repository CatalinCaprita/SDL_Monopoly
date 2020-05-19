#ifndef PROMPT_H
#define PROMPT_H
#include "Sprite.h"
#include "UILabel.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Button.h"
#include <string>
#include <vector>
class Prompt {
public:
	Prompt(const char *backPath,int unitX,int unitY, int unitW,int unitH,std::string& message);
	~Prompt();
	void updateXY(int byX = 0 , int byY = 0);
	void updateWH(int byW = 0, int byH = 0);
	void render();
	void setScale(int screenW,int screenH);
	void addButton( std::string& buttonName, Button* button);
	void switchText(std::string& newMessage);
	void setLifeTime(int ms);
	void decreaseLifeTime();
	int getW();
	int getH();
	bool isDone();
	bool canBeUpdated() {
		return bubble->candBeUpdated();
	}

private:
	Sprite* bubble;
	UILabel* text;
	std::vector<Button*> buttons;
	int lifeTime;
	int updateDelay;
};


#endif // !PROMPT_H
#pragma once
