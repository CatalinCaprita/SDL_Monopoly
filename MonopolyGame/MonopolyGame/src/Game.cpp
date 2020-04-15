#include "SDL.h"
#include "../headers/Game.h"
#include "../headers/TextureMaker.h"
int Game::count = 0;
Game::Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen) {
	int new_flag = 0;
	if (full_screen) {
		new_flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Game initialized";
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, new_flag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (window) {
			std::cout << "Window Popped. Fullscreen :" << full_screen << std::endl;
		}
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Up."<<std::endl;
		}
		TextureMaker::attach(renderer);
		background = TextureMaker::textureFromBMP("assets/background.bmp");
		playerTexture = TextureMaker::textureFromBMP("assets/pawn.bmp");
		if (!background || !playerTexture)
			isRunning = false;
		spriteFrame.h = 64;
		spriteFrame.w = 32;
		spriteFrame.x = 250;
		isRunning = true;
	}
	else {
		isRunning = false;
	}

}
Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

 void Game::listen_event() {
	 SDL_Event e;
	 SDL_PollEvent(&e);
	 switch (e.type) {
	 case SDL_QUIT:
		 isRunning = false;
		 break;
	 }
 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 SDL_RenderCopy(renderer, background, NULL, NULL);
	 SDL_RenderCopy(renderer, playerTexture, NULL,&spriteFrame);
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	 count++;
	 spriteFrame.x = count;
	 spriteFrame.y = count;
 }

