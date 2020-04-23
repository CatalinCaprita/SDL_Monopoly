#define PAWN_SIZE 25
#define NUMBER_OF_PLAYERS 4
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

Game::Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen) {
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
		background = TextureMaker::textureFromBMP("assets/background.bmp");
		spriteFrame.x = 0;
		spriteFrame.y = 0;
		spriteFrame.w = 1000;
		spriteFrame.h = 1000;

		if (!background || !playerTexture)
			isRunning = false;

		dice = new Dice();
		players.push_back(new Player("Player 1", "assets/blue.bmp", 930, 930, PAWN_SIZE, PAWN_SIZE));
		players.push_back(new Player("Player 2", "assets/red.bmp", 940, 930, PAWN_SIZE, PAWN_SIZE));
		players.push_back(new Player("Player 3", "assets/purple.bmp", 950, 930, PAWN_SIZE, PAWN_SIZE));
		players.push_back(new Player("Player 4", "assets/black.bmp", 960, 930, PAWN_SIZE, PAWN_SIZE));

		buttons.push_back(new Button("assets/buy_button.bmp", 1050, 590, 225, 80));
		buttons.push_back(new Button("assets/sell_button.bmp", 1050, 670, 225, 80));
		buttons.push_back(new Button("assets/end_turn_button.bmp", 1050, 750, 225, 80));

		background = TextureMaker::textureFromBMP("assets/background.bmp");
		if (!background)
			isRunning = false;
		isRunning = true;
		fillTiles("assets/houseProperties.txt");

		isRunning = true;
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
				 mouseY < dice->getFirstDieRect().y + dice->getFirstDieRect().h)
				 {
					 // If you press on the dice
					 /*
						TO DO
						Number of rolls + jail + not being able to roll 10 times/same turn
					 */
					 dice->roll(renderer);
					 for (int i = 0; i < dice->getFirstDieValue() + dice->getSecondDieValue(); i++) {
						 players[turn]->move();
						 players[turn]->update();
						 Game::render();
						 SDL_RenderPresent(renderer);
						 SDL_Delay(500);
					 }
				 }
			 else if (buttons[0]->hoverButton(mouseX, mouseY)){ 
				 std::cout << "button0" << std::endl;
			 }
			 else if (buttons[1]->hoverButton(mouseX, mouseY)){
				 std::cout << "button1" << std::endl;
			 }
			 else if (buttons[2]->hoverButton(mouseX, mouseY)){
				 turn++;
				 turn %= 4;
				 std::cout << "button2" << std::endl;
			 }
		 }
		 mousePressed = true;
	 }
	 else
		 mousePressed = false;

	 /*const Uint8* state = SDL_GetKeyboardState(NULL);
	 if (state[SDL_SCANCODE_Q]) {
		 players[0]->move();
	 }
	 if (state[SDL_SCANCODE_W]) {
		 players[1]->move();
	 }
	 if (state[SDL_SCANCODE_E]) {
		 players[2]->move();
	 }
	 if (state[SDL_SCANCODE_R]) {
		 dice->roll(renderer);
	 }*/
	 
 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 SDL_RenderCopy(renderer, background, NULL, &spriteFrame);
	 for (int i = 0; i < players.size(); i++)
		 players[i]->render(renderer);
	 dice->render(renderer);
	 for (int i = 0; i < buttons.size(); i++)
		 buttons[i]->render(renderer);
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	 for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
		 players[i]->update();
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

