#ifndef PROMPT_H
#define PROMPT_H
#include "Sprite.h"
#include "UILabel.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Button.h"
#include <string>
#include <vector>
/**
	Prompt class is used as a means to display messages to the screen. This is so because UILabel class only displays text physically on the screen
whereas for a propmt we also need a background. Prompt is basically a UILabel with a sprite acting as a background.
	Note that all the updates are done in game units as well.
*/
class Prompt {
public:
	Prompt(const char *backPath,int unitX,int unitY, int unitW,int unitH,std::string& message);
	~Prompt();
	void destroy();
	void updateXY(int byX = 0 , int byY = 0);
	void updateWH(int byW = 0, int byH = 0);
	void setTextWH(int unitW = 0, int unitH = 0);
	void render();
	void update();
	void setScale(int screenW,int screenH);
	void addButton(Button* button, int unitX, int unitY, int unitW, int unitH);
	void switchText(std::string& newMessage);
	void adjustText(int byX = 0, int byY = 0,int wrapSize = 0);
	void setLifeTime(int ms);
	void decreaseLifeTime();
	int getW();
	int getH();
	bool isDone();
	bool canBeUpdated() {
		return bubble->canBeUpdated();
	}
	bool isClicked();
	void setClickFadeable(bool value = true);
	bool isClickFadeable();
	bool isSumImput();
	bool isAcceptInput();
	void setSumInput( bool value = false);
	void setAcceptInput( bool value = false);
	Sprite* getBubbleSprite();

private:
	Sprite* bubble;
	UILabel* text;
	std::vector<Button*> buttons;
	int lifeTime;
	int updateDelay;
	bool fadeOnClick = true;
	bool sumInput;
	bool acceptInput;
};


#endif // !PROMPT_H
#pragma once
