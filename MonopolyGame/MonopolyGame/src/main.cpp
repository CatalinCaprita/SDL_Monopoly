#include <iostream>
#include <vector>
#include "../headers/Game.h"
#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000
#define FPS 120

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Game* instance = new Game("Monopoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_HEIGHT, WIN_WIDTH, false);
	const float frame_rate = 1000 / FPS;
	int frame_time = 0;
	int frame_start= 0;
	while (instance->running()) {
		frame_start = SDL_GetTicks();
		instance->listen_event();
		instance->update();
		instance->render();
		
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < frame_rate) {
			SDL_Delay(frame_rate - frame_time);
		}
	}
	return 0;
}