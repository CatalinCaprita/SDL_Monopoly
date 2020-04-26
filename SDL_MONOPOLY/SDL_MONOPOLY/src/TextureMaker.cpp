#include "../headers/TextureMaker.h"
SDL_Surface* TextureMaker::temp = NULL;
SDL_Renderer* TextureMaker::link = NULL;
TextureMaker::TextureMaker(){}
TextureMaker::~TextureMaker() {
	SDL_FreeSurface(temp);
}

void TextureMaker::attach(SDL_Renderer* ren) {
	link = ren;
}
SDL_Texture* TextureMaker::textureFromBMP(const char* path) {
	temp = SDL_LoadBMP(path);
	if (link == NULL)
		std::cout << "LINK IS NULL" << std::endl;
	if (temp == NULL) {
		std::cout << "Could not load Image: " << SDL_GetError() << std::endl;
		return NULL;
	}
	return SDL_CreateTextureFromSurface(link,temp);
}
SDL_Texture* TextureMaker::getWindowTexture(SDL_Window* win) {
	temp = SDL_GetWindowSurface(win);
	if (temp == NULL) {
		std::cerr << "Could not load from Window: " << SDL_GetError() << std::endl;
		return NULL;
	}
	return SDL_CreateTextureFromSurface(link,temp);

}
void TextureMaker::render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect) {
	SDL_RenderCopy(link, texture, srcRect, destRect);
}