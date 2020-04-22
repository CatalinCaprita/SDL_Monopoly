#include "SDL.h"
#include "../headers/TextureMaker.h"
#include <stdlib.h>
#include <time.h>


class Dice {
public:
	Dice();
	~Dice();
	void roll(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void update();
	int getFirstDieValue();
	int getSecondDieValue();
	SDL_Rect getFirstDieRect();
	SDL_Rect getSecondDieRect();
private:
	int firstDieValue;
	int secondDieValue;
	SDL_Rect firstDieRect;
	SDL_Rect secondDieRect;
	SDL_Texture* firstDieTexture;
	SDL_Texture* secondDieTexture;
};
