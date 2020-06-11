#pragma once
#include "../headers/TextureMaker.h"
#include "Sprite.h"
#include <string.h>
enum ButtonState{NORMAL = 0, HOVER = 1, CLICKED = 2};
class Button {
public:
	Button(const char* filePath, const char* filePathHover, const char* filePathClicked, int unitX, int unitY, int unitW, int unitH, ButtonState buttonState = NORMAL);
	~Button();
	void render();
	Sprite* getSprite();
	bool hoverButton(int, int);
	void updateButtonState(int mouseX, int mouseY);
	void update(int mouseX, int mouseY);
	const char* getPathModified(const char* c, int number);
private:
	Sprite* sprite;
	Sprite* spriteNormal;
	Sprite* spriteHover;
	Sprite* spriteClicked;
	ButtonState buttonState;
};