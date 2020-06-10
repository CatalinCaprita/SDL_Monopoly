#include "../headers/Prompt.h"
#include "../headers/Game.h"
#include <string>
#include <vector>
#include <unordered_map>
#define WHITE 0
#define BLACK 1
#define RED 2
SDL_Color colors[] = { {255,255,255,255},{0,0,0,0}, {205,92,92,50} };
Prompt::Prompt(const char* backPath, int unitX, int unitY, int unitW, int unitH, std::string& message) {
	bubble = new Sprite(backPath, unitW, unitH, unitX, unitY,-1,-1,true);
	text = new UILabel(unitX + 5, unitY + 5, unitW, unitH , message, TTF_OpenFont("assets/fonts/prompt_std2.ttf", 60), colors[BLACK]);
	bubble->setRenderDelay(10);
	updateDelay = 3;
};
Prompt::~Prompt() {
	delete bubble;
	delete text;
};
void Prompt::updateXY(int byX, int byY ) {
		bubble->update(byX, byY);
		text->updateXY(byX, byY);

};

void Prompt::updateWH(int byW, int byH) {
		bubble->updateUnitWidth(byW);
		bubble->updateUnitHeigth(byH);
		text->setWH( 0.75 * bubble->unitW(),0.5 * bubble->unitH());
		if (updateDelay == 0) {
			updateDelay = 3;
			
		}
		else updateDelay--;
}
void Prompt::render() {
	bubble->render();
	text->render();

};

void Prompt::setScale(int screenW, int screenH) {
	bubble->setScale(screenW, screenH);
	text->setScale(screenW, screenH);
	text->setLabelTexture(screenW);

};

void Prompt::addButton(std::string& buttonName,Button* button) {
	buttons.push_back(button);
}

void Prompt::switchText(std::string& newText) {
	text->setMessage(newText);
}

int Prompt::getW() {
	return bubble->unitW();
}

int Prompt::getH() {
	return bubble->unitH();
}

void Prompt::setLifeTime(int ms) {
	lifeTime = ms;
}

void Prompt::decreaseLifeTime() {
	if (lifeTime > 0 && bubble->canBeUpdated())
		lifeTime--;
}

bool Prompt::isDone() {
	return lifeTime > 0;
}

Sprite* Prompt::getBubbleSprite() {
	return bubble;
}