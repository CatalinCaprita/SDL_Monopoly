#pragma once
#include "SDL.h"
#include <vector>
#include "../headers/TextureMaker.h"
#include "../headers/Sprite.h"
#include "Tile.h"
#include "AbstractProperty.h"
#include <unordered_map>
class Player {
public:
	//Internals:
	Player(std::string name,const char*, int, int, int, int);
	~Player();
	void move();
	std::string& getName();
	void render();
	void update();
	void print();
	bool finishedMoving();
	void setRemainingSteps(int steps = 0, int direction = 1);
	void setSpriteScale(int, int);
	int getCurrentPosition();

	//Jail Functions
	bool isJailed();
	void goToJail();
	void freeFromJail();
	void setJailTurnsLeft(int);
	int getJailTurnsLeft();
	
	//Money And Property Management
	bool isBankrupt();
	int getMoney();
	int receiveMoney(int = 0);
	int payMoney(int = 0);
	void buyProperty(Tile*,const std::string& type);
	void sellProperty(Tile*);
	int getOwnedStations();
	int getOwnedUtils();
	bool ownsAllOfColor(Groups color);
	void destroyHousesFromColor(Groups color);
	void payPerBuildings();

	//Flag Setters
	int getFlag();
	void setJailFlag();
	void setCommandFlag();
	void setDiceFlag();

	Sprite* getSprite();

private:
	
	static int counter;
	/*
	flagType - used to decide which action is going to happend after the player finishes moving
	 - 0 finished a normal movement via Dice Roll
	 - 1 must be jailed
	 - 2 finished moving from a Chance or Community Chest Command 
	*/
	int  flagType;
	int direction;
	const int id;
	int totalMoney;
	int currentPosition;
	bool bankrupt;
	bool finishMoving;
	int remainingSteps;
	int renderDelay = 250;
	int lastRender;
	int jailTurnsLeft;
	std::string name;
	std::unordered_map<std::string,std::vector<Tile*> > ownedProperties;
	SDL_Rect spriteFrame;
	SDL_Texture* playerTexture;
	Sprite* sprite;
};