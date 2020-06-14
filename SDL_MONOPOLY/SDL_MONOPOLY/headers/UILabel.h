#pragma once
#ifndef UILABEL_H
#define UILABEL_H
#include "SDL.h"
#include "SDL_ttf.h"
#include "Sprite.h"
#include <string>
class UILabel {
public:
	UILabel(int unitX, int unitY, int unitW, int unitH, std::string& text, TTF_Font* font, SDL_Color& color);
	UILabel(Sprite* background, std::string& text, TTF_Font* font,  SDL_Color& color);
	virtual ~UILabel();
	void setLabelTexture(int wordWrapPixels = 0);
	void render();
	void updateXY(int byX = 0, int byY = 0);
	void updateWH(int byW = 0, int byH = 0);
	void setWH(int unitW, int unitH);
	void setScale(Sprite* scaleTo);
	void setScale(int screenW = 0 , int screenH = 0);
	void setMessage(std::string& newMessage);
	void appendText(char c);
	void popText();
	int unitW();
	int unitH();
	int size();
	std::string& getText();


private:
	SDL_Rect position;  //maintain the size of the text
	TTF_Font* labelFont;
	std::string labelText; //the text to be drawn
	SDL_Texture* labelTexture;
	SDL_Color textColor;
	float wRatio = 1.0f;
	float hRatio = 1.0f;
	int wrapSize;
};
#endif // !UILABEL_H
