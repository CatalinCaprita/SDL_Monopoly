#include "../headers/Dice.h"
Dice::Dice() {
	firstDieValue = 1;
	secondDieValue = 1;
	firstDieTexture = TextureMaker::textureFromBMP("assets/zar1.bmp");
	secondDieTexture = TextureMaker::textureFromBMP("assets/zar1.bmp");
	firstDieRect.x = 300; secondDieRect.x = 360;
	firstDieRect.y = secondDieRect.y = 300;
	firstDieRect.w = secondDieRect.w = firstDieRect.h = secondDieRect.h = 50;
	srand(time(NULL));
}
Dice::~Dice() {

}
void Dice::roll(SDL_Renderer* renderer) {
	std::string filepath1 = "";
	std::string filepath2 = "";
	for (int i = 0; i < 3; i++) {
		firstDieValue = rand() % 6 + 1;
		secondDieValue = rand() % 6 + 1;
		filepath1 = filepath1 + "assets/zar" + (char)('0' + firstDieValue) + ".bmp";
		filepath2 = filepath2 + "assets/zar" + (char)('0' + secondDieValue) + ".bmp";
		firstDieTexture = TextureMaker::textureFromBMP(filepath1.c_str());
		secondDieTexture = TextureMaker::textureFromBMP(filepath2.c_str());
		render(renderer);
		SDL_RenderPresent(renderer);
		filepath1 = "";
		filepath2 = "";
		SDL_Delay(300);
	}
}
void Dice::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, firstDieTexture, NULL, &firstDieRect);
	SDL_RenderCopy(renderer, secondDieTexture, NULL, &secondDieRect);
}
void Dice::update() {
}
int Dice::getFirstDieValue() {
	return firstDieValue;
}
int Dice::getSecondDieValue() {
	return secondDieValue;
}

SDL_Rect Dice::getFirstDieRect()
{
	return firstDieRect;
}

SDL_Rect Dice::getSecondDieRect()
{
	return secondDieRect;
}
