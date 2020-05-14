#pragma once
#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4018 ) 
#include "TextureMaker.h"
#include "SDL.h"
//1 worldUnit = screenWith / 1000 pixels;
class Sprite {
private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	float wRatio = 1.0f;
	float hRatio = 1.0f;
	int renderDelay;
	int lastRender;
public :
	int width, height;
	Sprite(const char* path, int unitW, int unitH,int unitX = 0,int unitY = 0,int screenW = -1, int screenH = -1,bool ignoresBG = false){
		texture = TextureMaker::textureFromBMP(path,ignoresBG);
		if (texture == NULL) {
			std::cout << "FAILED TO LOAD IMAGE AT " <<path <<std::endl;
		}
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
	~Sprite() {
		SDL_DestroyTexture(texture);
	}
	Sprite(Sprite* copy){
		wRatio = copy->wRatio;
		hRatio = copy->hRatio;
		destRect.w = copy->destRect.w;
		destRect.h = copy->destRect.h;
		destRect.x = copy->destRect.x;
		destRect.y = copy->destRect.y;
		lastRender = SDL_GetTicks();
		texture = copy->texture;
	}
	void copyScale(Sprite* otherSprite) {
		wRatio = otherSprite->wRatio;
		hRatio = otherSprite->hRatio;
		destRect.w = (int)width * wRatio;
		destRect.h = (int)height * hRatio;
	}
	void setPath(const char* newPath,bool ignoreBck = false) {
		texture = TextureMaker::textureFromBMP(newPath,ignoreBck);
	}
	
	void update(int xUnits, int yUnits) {
		destRect.x  += xUnits * wRatio;
		destRect.y  += yUnits * hRatio;
	}
	void updateTo(int xCoordUnits,int yCoordUnits) {
		destRect.x = xCoordUnits * wRatio;
		destRect.y = yCoordUnits * hRatio;

	}
	void render() {
		TextureMaker::render(texture, NULL, &destRect);
	}
	void setScale(int screenW, int screenH) {
		this->wRatio = (float)screenW / 100;
		this->hRatio = (float)screenH / 100;
		destRect.w = (int)width * wRatio;
		destRect.h = (int)height * hRatio;
		destRect.x *= wRatio;
		destRect.y *= hRatio;
	}

	void updateUnitWidth(int units) {
		destRect.w += units * wRatio;
	}

	void updateUnitHeigth(int units) {
		destRect.h += units * hRatio;
	}
	void setPixelXY(int pixelX, int pixelY) {
		destRect.x = pixelX / wRatio;
		destRect.y = pixelY / hRatio;
	}
	void setUnitXY(int xUnits, int yUnits) {
		destRect.x = xUnits * wRatio;
		destRect.y = yUnits * hRatio;

	}
	int unitX() {
		return destRect.x / wRatio;
	}
	int unitY() {
		return destRect.y / hRatio;
	}
	int pixelX() {
		return destRect.x ;
	}
	int pixelY() {
		return destRect.y ;
	}
	int pixelW() {
		return destRect.w;
	}
	int pixelH() {
		return destRect.h;
	}
	int unitW() {
		return destRect.w / (int)wRatio;
	}
	int unitH() {
		return destRect.h / (int)hRatio;
	}
	bool candBeUpdated() {
		if(SDL_GetTicks() - lastRender >= renderDelay) {
			lastRender = SDL_GetTicks();
			return true;
		}
		return false;
	}
	void setRenderDelay(int ms) {
		renderDelay = ms;
	}

};