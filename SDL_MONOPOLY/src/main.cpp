#include <iostream>
#include <vector>
#include "../headers/Game.h"
<<<<<<< HEAD
#define WIN_HEIGHT 1000
#define WIN_WIDTH 1300
#define FPS 120

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Game* instance = new Game("Monopoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, false);
=======
#include "../headers/TextureMaker.h"
#include "../headers/AbstractProperty.h"
#include "../headers/Groups.h"
#define WIN_HEIGHT 800
#define WIN_WIDTH 900
#define FPS 60
using namespace std;

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Game* instance = new Game("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH, WIN_HEIGHT, false);
>>>>>>> bbf50129cc713baef4db09224514aff1f60973a6
	const float frame_rate = 1000 / FPS;
	int frame_time = 0;
	int frame_start= 0;
	while (instance->running()) {
		frame_start = SDL_GetTicks();
		instance->listen_event();
		instance->update();
		instance->render();
<<<<<<< HEAD

=======
>>>>>>> bbf50129cc713baef4db09224514aff1f60973a6
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < frame_rate) {
			SDL_Delay(frame_rate - frame_time);
		}
	}
	return 0;
}