#include "SDL.h"
#include "../headers/Game.h"
#include "../headers/TextureMaker.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#define TILE_NUM 39
#define PROP_NUM 22
#define CARD_NUM 6
#define UTIL_NUM 2
#define UPPER_RENTS_BOUND 10
int Game::count = 0;

//Array of indexes for the HouseProperty properties
// tiles[propIdx[i]] = new HouseProperty();
int propIdx[] = { 1,3,			// BROWN
					6,8,9,		//LTBLUE				
					11,13,14,	//PURPLER
					16,18,19,	//ORANGE
					21,23,24,	//RED
					26,27,29,	//YELLOW
					31,32,34,	//GREEN
					37,39 };		//BLUE

//Array of indexes for the Card type
//tiles[cardIdx[i]] = new Card();
int cardIdx[] = { 2,7,17,22,33,36 };
int stationIdx[] = { 5,15,25,35 };
int utilIdx[] = { 12,28 };
int lastColor[] = { 3,9,14,19,24,29,34,39 };

Game::Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen) :tiles(TILE_NUM){
	int new_flag = 0;
	if (full_screen) {
		new_flag = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Game initialized";
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, new_flag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (window) {
			std::cout << "Window Popped. Fullscreen :" << full_screen << std::endl;
		}
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Up."<<std::endl;
		}
		TextureMaker::attach(renderer);
		background = TextureMaker::textureFromBMP("assets/board.bmp");
		playerTexture = TextureMaker::textureFromBMP("assets/pawn.bmp"); 
		if (!background || !playerTexture)
			isRunning = false;
		isRunning = true;
		fillTiles("assets/houseProperties.txt");
		players.push_back(new Player(tiles,"First Player"));
	}
	else {
		isRunning = false;
	}

}
Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

 void Game::listen_event() {
	 SDL_Event e;
	 SDL_PollEvent(&e);
	 switch (e.type) {
	 case SDL_QUIT:
		 isRunning = false;
		 break;
	 }
 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 SDL_RenderCopy(renderer, background, NULL, NULL);
	 SDL_RenderCopy(renderer, playerTexture, NULL,&spriteFrame);
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	 players[0]->move();
 }

 Groups getGroupId(int i) {
	 Groups color = RED;
	 switch (i) {
	 case 0: color = BROWN;
		 break;
	 case 1: color = LTBLUE;
		 break;
	 case 2: color = PURPLE;
		 break;
	 case 3: color = ORANGE;
		 break;
	 case 4: color = RED;
		 break;
	 case 5: color = YELLOW;
		 break;
	 case 6: color = GREEN;
		 break;
	 case 7: color = BLUE;
		 break;
	 }
	 return color;
 }

 std::string parse(const std::string & line, const char token) {
	 std::string result = "";
	 int pos = line.find(token);
	 int prev = 0;
	 while (pos != std::string::npos) {
		 result += line.substr(prev,pos - prev);
		 result += " ";
		 prev = pos + 1;
		 pos = line.find(token, pos + 1);
	 }
	 result += line.substr(prev, pos - prev);
	 return result;
 }
 void Game::fillTiles(const char *filePath) {
	 std::ifstream fin(filePath);
	 if (!fin) {
		 std::cout << "FILE NOT FOUND";
		 return;
	 }
	 int pid = 0, cid = 0, sid = 0, uid = 0;
	 int groupID;
	 std::string name;
	 int buyPrice, updateCost, rentStages;
	 std::vector<int>rentPrices(UPPER_RENTS_BOUND);	//dirty technique, but what can you do  `\ (' - ') /`
	 Groups color;
	 for (int i = 0; i < TILE_NUM; i++) {
		 //For HousePropery
		 if (pid < PROP_NUM  && i == propIdx[pid]) {
			 fin >> name >> buyPrice >> updateCost >> groupID;
			 name = parse(name, '_');
			 color = getGroupId(groupID);
			 rentStages = 6;
			 for (int i = 0; i < rentStages; i++)
				 fin >> rentPrices[i];
			 tiles[i] = new HouseProperty(name, buyPrice,updateCost,rentPrices,color);
			 tiles[i]->print();
			 pid++;
		 }
		 //For Station
	 }

 }

 
