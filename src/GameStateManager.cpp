#include "../headers/GameStateManager.h"
#include "../headers/GameState.h"
#include <vector>
#include <iostream>

GameStateManager* GameStateManager::instance = nullptr;

GameStateManager::GameStateManager():mousePressed(false){


}
GameStateManager::~GameStateManager(){
}

void GameStateManager::init(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen){
	instance = getInstance();
	window = SDL_CreateWindow(title, x_pos, y_pos, width + 300, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		SDL_SetRenderDrawColor(renderer, 204, 227, 199, 255);
		std::cout << "Renderer Initialized successfully!";
	}
	else
		std::cout << "RENDER INVALID";
}

SDL_Renderer* GameStateManager::getRenderer(){
	return renderer;
}

void GameStateManager::listen_event(){
	if(states.size() > 0)
		states[states.size() - 1]->listen_event();
}

void GameStateManager::render(){
	if (states.size() > 0)
		states[states.size() - 1]->render();
}

void GameStateManager::update(){
	if (states.size() > 0)
		states[states.size() - 1]->update();
}

void GameStateManager::pushState(GameState* state){
	states.push_back(state);
}

void GameStateManager::popState(){
	if (states.size() > 0) {
		delete states[states.size() - 1];
		states.pop_back();
	}
}

bool GameStateManager::running(){
	if(states.size() > 0)
		return (states[states.size() - 1]->running());
	return false;
}

