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
	const char* path;
public :
	int width, height;
	Sprite(const char* path, int unitW, int unitH, int unitX = 0, int unitY = 0, int screenW = -1, int screenH = -1, bool ignoresBG = false);
	~Sprite();
	Sprite(Sprite* copy);
	void copyScale(Sprite* otherSprite);
	void setPath(const char* newPath, bool ignoreBck = false);
	void update(int xUnits, int yUnits);
	void updateTo(int xCoordUnits, int yCoordUnits);
	void render();
	void setScale(int screenW, int screenH);
	void setRenderDelay(int ms);
	void updateUnitWidth(int units);
	void updateUnitHeigth(int units);
	void setPixelXY(int pixelX, int pixelY);
	void setUnitXY(int xUnits, int yUnits);

	int unitX();
	int unitY();
	int pixelX();
	int pixelY();
	int pixelW();
	int pixelH();
	int unitW();
	int unitH();

	float getWRatio();
	float getHRatio();
	bool candBeUpdated();
	bool isClicked();
	const char* getPath();
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* texture);
};