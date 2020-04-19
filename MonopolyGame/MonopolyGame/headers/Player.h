#pragma once
#include "SDL.h"
#include <vector>
#include "../headers/TextureMaker.h"
#include "../headers/Tile.h"
#include "../headers/AbstractProperty.h"
class Player {
public:
	Player(std::vector<Tile*>& properties, std::string name,const char*, int, int, int, int);
	~Player();
	void move(int = 0);
	std::string& getName();
	void render(SDL_Renderer*);
	void update();
	void print();
	bool isJailed();
	bool isBankrupt();
	int receiveMoney(int = 0);
	int payMoney(int = 0);
	void buyProperty(Tile*);
	void sellProperty(Tile*);

private:
	static int counter;
	const int id;
	int totalMoney;
	int currentPosition;
	bool jailed;
	bool bankrupt;
	std::string name;
	std::vector<Tile*>& ownedProperties;
	SDL_Rect spriteFrame;
	SDL_Texture* playerTexture;
};