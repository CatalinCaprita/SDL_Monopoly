#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "GameStateManager.h"

/*Virtual Class to be used as a top hierarchy for each of the states : Game or StartUp*/
class GameState {

public:
	GameState() {};
	virtual ~GameState() {};
	virtual void listen_event() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool running() = 0;

};
#endif // !GAMESTATE_H
