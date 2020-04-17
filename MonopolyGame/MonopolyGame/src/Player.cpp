#include "../headers/Player.h"
#define OFFSET 2
int Player::counter = 0;
int coordX[] = { 950, 820, 738, 656, 574, 492, 410, 328, 246, 164, 20,
				 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				 164, 246, 328, 410, 492, 574, 656, 738, 820, 950,
				 940, 940, 940, 940, 940, 940, 940, 940, 940, 940,
				}; // am scazut din primul 130 si dupa 82
int coordY[] = { 940, 940, 940, 940, 940, 940, 940, 940, 940, 940, 960,
				 820, 738, 656, 574, 492, 410, 328, 246, 164, 60,
				 40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
				 164, 246, 328, 410, 492, 574, 656, 738, 820, 950
				};

Player::Player(const char* filepath, int xpos, int ypos, int height, int width) : id(counter), position(0){
	counter++;
	spriteFrame.x = xpos;
	spriteFrame.y = ypos;
	spriteFrame.h = height;
	spriteFrame.w = width;
	playerTexture = TextureMaker::textureFromBMP(filepath);
}

Player::~Player() {
}

void Player::move(int value) {
	position += value;
	position %= 40;
	SDL_Delay(200);
}

void Player::update() {
	spriteFrame.x = coordX[position] + (id - OFFSET) * 10;
	spriteFrame.y = coordY[position];
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, playerTexture, NULL, &spriteFrame);
}