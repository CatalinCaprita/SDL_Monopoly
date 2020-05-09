#pragma once
#ifndef TEXTUREMAKER_H
#define TEXTUREMAKER_H
#include "SDL.h"
#include <iostream>
class TextureMaker{
public:
	//returns SDL_texture from bmp style image
	//params : the file path of the immage, preferabliy set in ../assets
	static SDL_Texture *textureFromBMP(const char* path,bool ignoreBg = false);
	static SDL_Texture* getWindowTexture(SDL_Window * win);

	//Changes the Renderer object pointed to by _link
	//To be used whenever you need to load an Image. Use with the game's inner renderer field 
	static void attach(SDL_Renderer* ren);
	static void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect *destRect);
	TextureMaker* factory() {
		if (self == NULL)
			self = new TextureMaker();
		return self;
	}
private:
	static TextureMaker* self;
	static SDL_Surface* temp;
	static SDL_Renderer* link;
	TextureMaker();
	~TextureMaker();

};

#endif // !TEXTUREMAKER_H

