#pragma once
#include "SDL.h"
#include <vector>
#include "../headers/TextureMaker.h"
#include "../headers/Tile.h"
#include "../headers/AbstractProperty.h"
class Player {
public:
	Player(std::string name,const char*, int, int, int, int);
	~Player();
	void move();
	std::string& getName();
	void render(SDL_Renderer*);
	void update();
	void print();
	bool isJailed();
	void goToJail();
	void freeFromJail();
	void setJailTurnsLeft(int);
	int getJailTurnsLeft();
	bool isBankrupt();
	int receiveMoney(int = 0);
	int payMoney(int = 0);
	void buyProperty(Tile*);
	void sellProperty(Tile*);
	int getCurrPosition();

private:
	static int counter;
	const int id;
	int totalMoney;
	int currentPosition;
	int jailTurnsLeft;
	bool bankrupt;
	std::string name;
	std::vector<Tile*> ownedProperties;
	SDL_Rect spriteFrame;
	SDL_Texture* playerTexture;
};