#include "SDL.h"
#include "../headers/TextureMaker.h"
#include "../headers/Sprite.h"
#include <stdlib.h>
#include <time.h>


class Dice {
public:
	Dice();
	~Dice();
	void roll(SDL_Renderer* renderer);
	void render();
	void update();
	int getFirstDieValue();
	int getSecondDieValue();
	Sprite* getFirstDieSprite();
	Sprite* getSecondDieSprite();
	bool thrownDouble();
	void setBlocked(bool);
	bool isBlocked();
private:
	bool blocked;
	int firstDieValue;
	int secondDieValue;
	Sprite* firstDieSprite;
	Sprite* secondDieSprite;
};
