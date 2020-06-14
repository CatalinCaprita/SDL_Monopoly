#include "../headers/TextureMaker.h"
#include "../headers/Game.h"
SDL_Surface* TextureMaker::temp = NULL;
SDL_Renderer* TextureMaker::link = Game::getRenderer();
TextureMaker::TextureMaker(){}
TextureMaker::~TextureMaker() {
	SDL_FreeSurface(temp);
}

void TextureMaker::attach(SDL_Renderer* ren) {
	link = ren;
}
SDL_Texture* TextureMaker::textureFromBMP(const char* path,bool ignoreBg) {
	temp = SDL_LoadBMP(path);
	if (temp == NULL) {
		std::cout << "Could not load Image: " << SDL_GetError() << std::endl;
		return NULL;
	}
	if (ignoreBg) {
		Uint32 colorkey = SDL_MapRGB(temp->format, 0, 0, 0);
		SDL_SetColorKey(temp, SDL_TRUE, colorkey);
	}
	return SDL_CreateTextureFromSurface(Game::getRenderer(),temp);
}
SDL_Texture* TextureMaker::getWindowTexture(SDL_Window* win) {
	temp = SDL_GetWindowSurface(win);
	if (temp == NULL) {
		std::cerr << "Could not load from Window: " << SDL_GetError() << std::endl;
		return NULL;
	}
	return SDL_CreateTextureFromSurface(Game::getRenderer(),temp);

}
void TextureMaker::render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect) {
	SDL_RenderCopy(Game::getRenderer(), texture, srcRect, destRect);
}