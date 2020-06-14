#include "../headers/Dice.h"
Dice::Dice() {
	blocked = false;
	firstDieValue = 1;
	secondDieValue = 1;
	firstDieSprite = new Sprite("assets/zar2.bmp", 8, 9, 106, 88);
	secondDieSprite = new Sprite("assets/zar2.bmp", 8, 9, 116, 88);
	/**
	firstDieRect.x = 300; secondDieRect.x = 360;
	firstDieRect.y = secondDieRect.y = 300;
	firstDieRect.w = secondDieRect.w = firstDieRect.h = secondDieRect.h = 50;
	*/
	srand(time(NULL));
}
Dice::~Dice() {

}
void Dice::roll(SDL_Renderer* renderer) {
	std::string filepath1 = "";
	std::string filepath2 = "";
	for (int i = 0; i < 4; i++) {
		firstDieValue = rand() % 6 + 1;
		secondDieValue = rand() % 6 + 1;
		filepath1 = filepath1 + "assets/zar" + (char)('0' + firstDieValue) + ".bmp";
		filepath2 = filepath2 + "assets/zar" + (char)('0' + secondDieValue) + ".bmp";
		firstDieSprite->setPath(filepath1.c_str());
		secondDieSprite->setPath(filepath2.c_str());
		render();
		SDL_RenderPresent(renderer);
		filepath1 = "";
		filepath2 = "";
		SDL_Delay(300);
	}
}
void Dice::render() {
	firstDieSprite->render();
	secondDieSprite->render();
}
void Dice::update() {
}
int Dice::getFirstDieValue() {
	return firstDieValue;
}
int Dice::getSecondDieValue() {
	return secondDieValue;
}

Sprite* Dice::getFirstDieSprite()
{
	return firstDieSprite;
}

Sprite* Dice::getSecondDieSprite()
{
	return secondDieSprite;
}

bool Dice::thrownDouble()
{
	return firstDieValue == secondDieValue;
}

void Dice::setBlocked(bool blocked) {
	this->blocked = blocked;
}

bool Dice::isBlocked() {
	return blocked;
}