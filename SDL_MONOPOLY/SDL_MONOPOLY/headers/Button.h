#pragma once
#include "../headers/TextureMaker.h"
#include "Sprite.h"
#include <string.h>
enum ButtonState{NORMAL = 0, HOVER = 1};
class Button {
public:
	Button(const char* filePath, const char* filepathHover, int unitX, int unitY, int unitW, int unitH, ButtonState buttonState = NORMAL);
	~Button();
	void render();
	Sprite* getSprite();
	bool hoverButton(int, int);
	void update(int mouseX, int mouseY);
	const char* getPathModified(const char* c, int number);
private:
	Sprite* sprite;
	Sprite* spriteHover;
	Sprite* spriteNormal;
	ButtonState buttonState;
};