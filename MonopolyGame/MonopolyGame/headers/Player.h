#pragma once
#include "SDL.h"
#include "../headers/TextureMaker.h"
using namespace std;
class Player {

private:
	static int counter;
	const int id;
	int position;
	SDL_Rect spriteFrame;
	SDL_Texture* playerTexture;
public:
	Player(const char* = "", int = 0, int = 0, int = 0, int = 0);
	~Player();
	void move(int = 0);
	void render(SDL_Renderer*);
	void update();
};