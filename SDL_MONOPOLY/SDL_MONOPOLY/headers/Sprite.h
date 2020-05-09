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
	}
	~Sprite() {
		SDL_DestroyTexture(texture);
	}
	Sprite(Sprite* copy){
		wRatio = copy->wRatio;
		hRatio = copy->hRatio;
		width = copy->width;
		height = copy->height;
		texture = copy->texture;
	}
	void setPath(const char* newPath) {
		texture = TextureMaker::textureFromBMP(newPath);
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
};