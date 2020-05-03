#pragma once
#include "SDL.h"
#include <vector>
#include "../headers/TextureMaker.h"
#include "../headers/Tile.h"
#include "../headers/AbstractProperty.h"
#include "../headers/Sprite.h"
class Player {
public:
	Player(std::string name,const char*, int, int, int, int);
	~Player();
	void move();
	std::string& getName();
	void render();
	void update();
	void print();
	bool isJailed();
	bool isBankrupt();
	bool finishedMoving();
	
	int receiveMoney(int = 0);
	int payMoney(int = 0);
	int getCurrentPosition();
	void setJailFlag();
	void gotToJail();
	void freeFromJail();
	void setJailTurnsLeft(int);
	int getJailTurnsLeft();
	void buyProperty(Tile*);
	void sellProperty(Tile*);
	void setRemainingSteps(int);
	void setSpriteScale(int, int);

	Sprite* getSprite();

private:
	static int counter;
	const int id;
	int totalMoney;
	int currentPosition;
	bool mustBeJailed;
	bool bankrupt;
	bool finishMoving;
	int remainingSteps;
	int renderDelay = 250;
	int lastRender;
	int jailTurnsLeft;
	std::string name;
	std::vector<Tile*> ownedProperties;
	SDL_Rect spriteFrame;
	SDL_Texture* playerTexture;
	Sprite* sprite;
	int x, y;
};