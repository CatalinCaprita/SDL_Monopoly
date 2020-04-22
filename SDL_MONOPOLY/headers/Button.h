#pragma once
#include "../headers/TextureMaker.h"
class Button {
public:
	Button(const char*, int, int, int, int);
	~Button();
	void render(SDL_Renderer* renderer);
	SDL_Rect getButtonFrame();
	SDL_Texture* getButtonTexture();
	bool hoverButton(int, int);
private:
	SDL_Rect buttonFrame;
	SDL_Texture* buttonTexture;
};