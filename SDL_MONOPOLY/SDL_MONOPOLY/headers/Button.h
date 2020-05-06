#pragma once
#include "../headers/TextureMaker.h"
#include "Sprite.h"
class Button {
public:
	Button(const char* filePath, int unitX, int unitY, int unitW, int unitH);
	~Button();
	void render();
	Sprite* getSprite();
	bool hoverButton(int, int);
private:
	Sprite* sprite;
};