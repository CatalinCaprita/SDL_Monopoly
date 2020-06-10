#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SDL.h"
#include "SDL_ttf.h"
#include "Sprite.h"
#include "Prompt.h"

class TextBox : public Prompt{
public:
	TextBox(const char* backPath, int unitX, int unitY, int unitW, int unitH, std::string& message);
	~TextBox();
	void update();


private:
	UILabel* shownText;
	Sprite* textArea;
	bool isFocused;


};
#include <string>
#endif // !TEXTBOX_H
