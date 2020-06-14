#include "../headers/UILabel.h"
#include "../headers/Game.h"
UILabel:: UILabel(int unitX, int unitY, int unitW, int unitH, std::string& text, TTF_Font* font, SDL_Color& color) : labelText(text), labelFont(font), textColor(color) {
	TTF_Init();
	if (labelFont == nullptr) {
		std::cerr << "Label font path iw wrong! \n "<<TTF_GetError();
	}
	position.x = unitX;
	position.y = unitY;
	position.w = unitW;
	position.h = unitH;
	//setLabelTexture();
};

UILabel::UILabel(Sprite* background, std::string& text, TTF_Font* font, SDL_Color& color) : labelText(text), labelFont(font), textColor(color) {
	wRatio = background->getWRatio();
	hRatio = background->getHRatio();
	position.w = background->pixelW();
	position.h = background->pixelH();
	position.x = background->pixelX();
	position.y = background->pixelY();
	//setLabelTexture();
}
UILabel::~UILabel() {
	SDL_DestroyTexture(labelTexture);
	TTF_CloseFont(labelFont);
};

void UILabel::setLabelTexture(int wordWrapPixels) {
	wrapSize = wordWrapPixels;
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(labelFont, labelText.c_str(), textColor, wrapSize);
	if(labelTexture)
		SDL_DestroyTexture(labelTexture);
	labelTexture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
	SDL_FreeSurface(surface);
};
void UILabel::render() {
	TextureMaker::render(labelTexture, NULL, &position);
};
void UILabel::updateXY(int byUnitsX,int byUnitsY) {
	position.x += byUnitsX * wRatio;
	position.y += byUnitsY * hRatio;
};
void UILabel::updateWH(int byUnitsW, int byUnitsH) {
	position.w += byUnitsW * wRatio;
	position.h += byUnitsH * hRatio;
};

void UILabel::setScale(int screenW, int screenH) {
	wRatio = screenW / 100;
	hRatio = screenH / 100;
	position.w *= wRatio;
	position.h *= hRatio;
	position.x *= wRatio;
	position.y *= hRatio;
}
void UILabel::setMessage(std::string& newMessage) {
	labelText = newMessage;
	setLabelTexture(wrapSize);
}

void UILabel::appendText(const char c) {
	labelText.append(1,c);
	setLabelTexture(wrapSize);
}

void UILabel::popText() {
	if (labelText.size() > 0) {
		labelText.pop_back();
		setLabelTexture(wrapSize);
	}
}
void UILabel::setWH(int unitW, int unitH) {
	position.w = unitW *  wRatio;
	position.h = unitH *hRatio;

}

int UILabel::unitW() {
	return position.w / wRatio;
}
int UILabel::unitH() {
	return position.h / hRatio;
}

int UILabel::size() {
	return labelText.size();
}

std::string& UILabel::getText(){
	return labelText;
}
