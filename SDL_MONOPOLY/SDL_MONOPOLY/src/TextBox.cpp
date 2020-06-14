#include "../headers/TextBox.h"
#include "../headers/Game.h"
SDL_Color BLACK = { 0,0,0,0 };
int lastClickX = 0;
int lastClickY = 0;
std::string crs = "|";
std::string text = " ";
int lastTick = 0; 
TextBox::TextBox(const char* backPath, int unitX, int unitY, int unitW, int unitH, std::string& message){
	textArea = new Sprite(backPath, unitW, unitH, unitX, unitY,-1,-1,true);
	shownText = new UILabel(unitX + 2, unitY + 1, unitW, unitH / 2, message, TTF_OpenFont("assets/fonts/prompt_std2.ttf", 60), BLACK);
	shownText->setWH(1, unitH / 2);
	cursor = new UILabel(unitX + 3, unitY, 1, unitH * 0.75, crs, TTF_OpenFont("assets/fonts/prompt_std2.ttf", 60), BLACK);
	textArea->setRenderDelay(1000);
	isFocused = false;
	tickCursor = false;

}

TextBox::~TextBox(){
	delete textArea;
	delete shownText;
	delete cursor;
}

SDL_Rect& TextBox::getRect() {
	return textArea->getRect();
}

std::string& TextBox::getInput()
{
	return shownText->getText();
}

void TextBox::update(){
	if (textArea->isClicked()) {
		std::cout << "FOCUSED";
		lastClickX = Game::getClickX();
		lastClickY = Game::getClickY();
		isFocused = true;
	}
	else if(Game::getClickX() != lastClickX && Game::getClickY() != lastClickY){
		isFocused = false;
	}
	if (isFocused) {
		if (Game::isEnter()) {
			isFocused = false;
			textReturn = true;
			Game::setEnterFlag(false);
		}
		if(Game::isBack() && shownText->size() > 0){
			shownText->updateWH(-2, 0);
			shownText->popText();
			cursor->updateXY(-2, 0);
			Game::setBackFlag(false);
		}
		else if (Game::isStroke() && shownText->unitW() < textArea->unitW() - 5) {
			shownText->updateWH(2, 0);
			shownText->appendText(Game::getInChar());
			cursor->updateXY(2, 0);
			Game::setKeyStroke(false);
		}
		if (textArea->canBeUpdated()) {
			//Make cursor visible 
			tickCursor = true;
			lastTick = SDL_GetTicks();
		}
	}
}

void TextBox::setScale(int screenW,int screenH) {
	textArea->setScale(screenW, screenH);
	shownText->setScale(screenW, screenH);
	shownText->setLabelTexture(screenW);
	cursor->setScale(screenW, screenH);
	cursor->setLabelTexture(screenW);
}
void TextBox::render() {
	textArea->render();
	shownText->render();
	if (tickCursor) {
		cursor->render();
		if (SDL_GetTicks() - lastTick >= 250) {
			tickCursor = false;
			lastTick = SDL_GetTicks();
		}
	}
}
bool TextBox::isReturn() {
	if (textReturn == true) {
		textReturn = false;
		return true;
	}
	return textReturn;
}