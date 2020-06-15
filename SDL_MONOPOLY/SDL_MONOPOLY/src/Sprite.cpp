#include "../headers/Sprite.h"
#include "../headers/Game.h"
#include "../headers/GameStateManager.h"

Sprite::Sprite(const char* path, int unitW, int unitH, int unitX, int unitY , int screenW , int screenH, bool ignoresBG ) {
	texture = TextureMaker::textureFromBMP(path, ignoresBG);
	if (texture == NULL) {
		std::cout << "FAILED TO LOAD IMAGE AT " << path << std::endl;
	}
	this->path = path;
	this->width = unitW; //number of units
	this->height = unitH; // number of units
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = unitX;
	destRect.y = unitY;
	if (screenW > -1 && screenH > -1) {
		setScale(screenW, screenH);
	}
	lastRender = SDL_GetTicks();
	renderDelay = 100;
}
Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
}
Sprite::Sprite(Sprite* copy) {
	wRatio = copy->wRatio;
	hRatio = copy->hRatio;
	destRect.w = copy->destRect.w;
	destRect.h = copy->destRect.h;
	destRect.x = copy->destRect.x;
	destRect.y = copy->destRect.y;
	lastRender = SDL_GetTicks();
	
}
void Sprite::copyScale(Sprite* otherSprite) {
	wRatio = otherSprite->wRatio;
	hRatio = otherSprite->hRatio;
	destRect.w = (int)width * wRatio;
	destRect.h = (int)height * hRatio;
}
void Sprite::setPath(const char* newPath, bool ignoreBck) {
	if (path != newPath) {

		if (texture) {
			SDL_DestroyTexture(texture);
		}
		texture = TextureMaker::textureFromBMP(newPath, ignoreBck);
	}
	

}
bool Sprite::isClicked() {
	return GameStateManager::getInstance()->mouseClick() 
		&& destRect.x <= GameStateManager::getInstance()->getClickX() 
		&& GameStateManager::getInstance()->getClickX() <= destRect.x + destRect.w
		&& destRect.y <= GameStateManager::getInstance()->getClickY() 
		&& GameStateManager::getInstance()->getClickY() <= destRect.y + destRect.h;
}
void Sprite::update(int xUnits, int yUnits) {
	destRect.x += xUnits * wRatio;
	destRect.y += yUnits * hRatio;
}
void Sprite::updateTo(int xCoordUnits, int yCoordUnits) {
	destRect.x = xCoordUnits * wRatio;
	destRect.y = yCoordUnits * hRatio;

}
void Sprite::render() {
	TextureMaker::render(texture, NULL, &destRect);
}
void Sprite::setScale(int screenW, int screenH) {
	this->wRatio = (float)screenW / 100;
	this->hRatio = (float)screenH / 100;
	destRect.w = (int)width * wRatio;
	destRect.h = (int)height * hRatio;
	destRect.x *= wRatio;
	destRect.y *= hRatio;
}

void Sprite::updateUnitWidth(int units) {
	destRect.w += units * wRatio;
}

void Sprite::updateUnitHeigth(int units) {
	destRect.h += units * hRatio;
}
void Sprite::setPixelXY(int pixelX, int pixelY) {
	destRect.x = pixelX / wRatio;
	destRect.y = pixelY / hRatio;
}
void Sprite::setUnitXY(int xUnits, int yUnits) {
	destRect.x = xUnits * wRatio;
	destRect.y = yUnits * hRatio;

}
int Sprite::unitX() {
	return destRect.x / wRatio;
}
int Sprite::unitY() {
	return destRect.y / hRatio;
}
int Sprite::pixelX() {
	return destRect.x;
}
int Sprite::pixelY() {
	return destRect.y;
}
int Sprite::pixelW() {
	return destRect.w;
}
int Sprite::pixelH() {
	return destRect.h;
}
int Sprite::unitW() {
	return destRect.w / (int)wRatio;
}
int Sprite::unitH() {
	return destRect.h / (int)hRatio;
}
bool Sprite::canBeUpdated() {
	if (SDL_GetTicks() - lastRender >= renderDelay) {
		lastRender = SDL_GetTicks();
		return true;
	}
	return false;
}
const char* Sprite::getPath() { return path; }

void Sprite::setRenderDelay(int ms) {
	renderDelay = ms;
}

float Sprite::getWRatio() {
	return wRatio;
}
float Sprite::getHRatio() {
	return hRatio;
}
SDL_Texture* Sprite::getTexture() { return texture; }

SDL_Rect& Sprite::getRect() {
	return destRect;
}
void Sprite::setTexture(SDL_Texture* texture) {
	this->texture = texture;
}
