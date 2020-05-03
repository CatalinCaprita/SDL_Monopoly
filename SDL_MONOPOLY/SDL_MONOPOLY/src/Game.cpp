#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4018 ) 
#include "../headers/Game.h"
#include "../headers/TextureMaker.h"
#include "../headers/UserAnimator.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#define TILE_NUM 39
#define PROP_NUM 22
#define CARD_NUM 6
#define UTIL_NUM 2
#define STATION_NUM 4
#define CORNER_NUM 4
#define UPPER_RENTS_BOUND 10
#define PAWN_SIZE 2			 //changing to GAME UNITS
#define NUMBER_OF_PLAYERS 4
#define START_X 88
#define START_Y 89
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
int Game::nrDoublesThrown = 0;
Game::Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen):tiles(40){
		dice = new Dice();
	mousePressed = false;
	turn = 0;
	int new_flag = 0;
	if (full_screen) {
		new_flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, new_flag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		TextureMaker::attach(renderer);
		UserAnimator::attach(this);
		background = new Sprite("assets/board.bmp", width, height, 0, 0);
		if (!background)
			isRunning = false;
		background->setScale(100, 100);	
		this->screenWidth = width;
		this->screenHeight = height;
		dice = new Dice();
		players.push_back(new Player("Player 1", "assets/blue.bmp",START_X,START_Y,2,4));
		players[0]->setSpriteScale(width, height);
		players.push_back(new Player("Player 2", "assets/red.bmp", START_X + 1, START_Y -1 , PAWN_SIZE, PAWN_SIZE));
		players[1]->setSpriteScale(width, height);
		/*
		players.push_back(new Player("Player 3", "assets/purple.bmp", 950, 930, PAWN_SIZE, PAWN_SIZE));
		players.push_back(new Player("Player 4", "assets/black.bmp", 960, 930, PAWN_SIZE, PAWN_SIZE));
		*/
		buttons.push_back(new Button("assets/buy_button.bmp", 300, 390, 225, 80));
		buttons.push_back(new Button("assets/sell_button.bmp", 300, 470, 225, 80));
		buttons.push_back(new Button("assets/end_turn_button.bmp", 300, 550, 225, 80));
		isRunning = true;
		fillTiles("assets/houseProperties.txt");
		for (int i = 0; i < tiles.size(); i++) {
			tiles[i]->print();
		}
	}
	else {
		isRunning = false;
	}

}
Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
SDL_Renderer* Game::getRenderer() {
	return renderer;
}

int Game::getScreenW() {
	return screenWidth;
}
int Game::getScreenH() {
	return screenHeight;
}

SDL_Window* Game::getWindow() {
	return window;
}
 void Game::listen_event() {
	 SDL_Event e;
	 int mouseX, mouseY;
	 SDL_PollEvent(&e);
	 SDL_PumpEvents();

	 if (e.type == SDL_QUIT)
		 isRunning = false;

	 if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) { 
		 if (!mousePressed) {

			 if (mouseX > dice->getFirstDieRect().x&&
				 mouseX < dice->getSecondDieRect().x + dice->getSecondDieRect().w &&
				 mouseY > dice->getFirstDieRect().y&&
				 mouseY < dice->getFirstDieRect().y + dice->getFirstDieRect().h) {
				 if (!dice->isBlocked()) {
					 dice->roll(renderer);
					 std::cout << "Ai dat " << dice->getFirstDieValue() + dice->getSecondDieValue() << std::endl;
					 if (players[turn]->isJailed()) {
						 if (dice->thrownDouble()) {
							 players[turn]->freeFromJail();
						 }
						 else {
							 int turns = players[turn]->getJailTurnsLeft();
							 players[turn]->setJailTurnsLeft(turns - 1); // decrement jail turn left for players at current turn
						 }
						 dice->setBlocked(true);
						 Game::nrDoublesThrown = 0;
					 }
					 else {
						 if (dice->thrownDouble()) {
							 Game::nrDoublesThrown++;
						 }

						 if (Game::nrDoublesThrown == 3) {
							 players[turn]->setRemainingSteps(50 - players[turn]->getCurrentPosition());
							 players[turn]->setJailFlag(); //Player is now in moving, once it will finish, it will go direcly to jail
							 dice->setBlocked(true); //Set the dice block so while the current player is moving nobody can run the dice;
						 }
						 else {
							 /*
							 for (int i = 0; i < dice->getFirstDieValue() + dice->getSecondDieValue(); i++) {
								 players[turn]->move();
								 players[turn]->update();
								 Game::render();
								 SDL_RenderPresent(renderer);
								 SDL_Delay(300);
								
							 }
							 Ca sa va faceti o idee, faceti paralela cu ceea ce e in Player::update(). Se intmapla acelasi lucru ca la voi, 
							 Doar ca o sa am nevoie doar de o update() si o sa ma misc la fiecare Game::render, in loc sa redesenez totul doar in for 
							 */

							 players[turn]->setRemainingSteps(dice->getFirstDieValue() + dice->getSecondDieValue()); 
							 dice->setBlocked(true);
							 if (!dice->thrownDouble()) {
								 dice->setBlocked(true);
								 Game::nrDoublesThrown = 0;
							 }
						 }
					 }
				 }
			 }
			 else if (buttons[0]->hoverButton(mouseX, mouseY)) {
				 std::cout << "button0" << std::endl;
			 }
			 else if (buttons[1]->hoverButton(mouseX, mouseY)) {
				 std::cout << "button1" << std::endl;
			 }
			 else if (buttons[2]->hoverButton(mouseX, mouseY)) {
				 turn++;
				 turn %= 2;
				 dice->setBlocked(false);
				 std::cout << "button2" << std::endl;
			 }
		 }
		 mousePressed = true;
	 }
	 else
		 mousePressed = false;

 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 background->render();
	 for (int i = 0; i < players.size(); i++)
		 players[i]->render();
	 dice->render(renderer);
	 for (int i = 0; i < buttons.size(); i++)
		 buttons[i]->render(renderer);
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	 for (int i = 0; i < players.size(); i++) {
		 players[i]->update();
		 /*
		 Daca la iteratia curenta a Game::update() playerul a carui tura e a terminat sa de mutat ,i.e. remainingSteps == 0,
		 se intampla interactiunea cu tile-ul
		 */
		 if (players[turn]->finishedMoving()) {
			tiles[players[turn]->getCurrentPosition()]->doEffect(players[turn]);
		 }
	 }
	 dice->update();
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
	 case 10: color = STATION;
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
	 std::string command;
	 int buyPrice, updateCost, rentStages;
	 std::vector<int>rentPrices(UPPER_RENTS_BOUND);	//dirty technique, but what can you do  `\ (' - ') /`
	 Groups color;
	 tiles[4] = new CommandTile("Income Tax");
	 tiles[38] = new CommandTile("Luxury Tax");
	 for (int i = 0; i < tiles.size(); i++) {
		 //For HouseProperty
		 if (pid < PROP_NUM  && i == propIdx[pid]) {
			 fin >> name >> buyPrice >> updateCost >> groupID;
			 name = parse(name, '_');
			 color = getGroupId(groupID);
			 rentStages = 6;
			 for (int i = 0; i < rentStages; i++)
				 fin >> rentPrices[i];
			 tiles[i] = new HouseProperty(name, buyPrice,updateCost,rentPrices,color,i);
		
			 pid++;
		 }
		 //For StationProperty
		 else if (sid < STATION_NUM && i == stationIdx[sid]) {
			 fin >> name;
			 name = parse(name, '_');
			 tiles[i] = new StationProperty(name,200,0,STATION,i);
		
			 sid++;
		 }
		 //For UtilityProperty
		 else if (uid < UTIL_NUM && i == utilIdx[uid]) {
			 fin >> name;
			 name = parse(name, '_');
			 tiles[i] = new UtilityProperty(name, 150, 0, UTIL, i);
		
			 uid++;
		 }
		 //For Corners
		 else if (i % 10 == 0) {
			 fin >> name >> command;
			 name = parse(name, '_');
			 command = parse(command, '_');
			 tiles[i / 10 * 10 ] = new Corner(name,command,i / 10);

		 }
		 //For Chance, Community Chest, Income Tax and Luxury Tax
		 else if (cid < CARD_NUM && i == cardIdx[cid]) {
			 if (cid % 2 == 0)
				 tiles[i] = new CommandTile("Community Chest");
			 else
				 tiles[i] = new CommandTile("Chance");
			 cid++;
		 }
	 }

 }

