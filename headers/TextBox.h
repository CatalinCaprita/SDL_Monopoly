#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SDL.h"
#include "SDL_ttf.h"
#include "Sprite.h"
#include "Prompt.h"

class TextBox{
public:
	TextBox(const char* backPath, int unitX, int unitY, int unitW, int unitH, std::string& message);
	~TextBox();
	void update();
	void render();
	void setScale(int screenW, int screenH);
	bool isReturn();
	SDL_Rect& getRect();
	std::string& getInput();

private:
	UILabel* shownText;
	UILabel* cursor;
	Sprite* textArea;
	bool tickCursor;
	bool isFocused;
	bool textReturn;


};
#include <string>
#endif // !TEXTBOX_H
