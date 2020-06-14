#include <iostream>
#include <vector>
#include "../headers/Game.h"
#include "../headers/GameStateManager.h"
#include "../headers/StartUpState.h"
#define WIN_HEIGHT 800
#define WIN_WIDTH  1000
#define FPS 65

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	GameStateManager::getInstance()->init("Monopoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, false);
	GameStateManager::getInstance()->pushState(new StartUpState(WIN_WIDTH, WIN_HEIGHT));
	const float frame_rate = 1000 / FPS;
	int frame_time = 0;
	int frame_start= 0;
	while (GameStateManager::getInstance()->running()) {
		frame_start = SDL_GetTicks();
		GameStateManager::getInstance()->listen_event();
		GameStateManager::getInstance()->update();
		GameStateManager::getInstance()->render();
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < frame_rate) {
			SDL_Delay(frame_rate - frame_time);
		}
	}
	return 0;
}