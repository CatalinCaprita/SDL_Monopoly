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

#define DICE_MOVE 0
#define MUST_BE_JAILED 1
#define EXEC_COMMAND 2
#define BUYER_TRADE 4
#define OWNER_TRADE 3


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
Dice* Game::dice = nullptr;
SDL_Renderer* Game::renderer = nullptr;
int last = 0;
int globalSum = 0;
int Game::count = 0;
int Game::mouseX = 0;
int Game::mouseY = 0;
int Game::clickX = 0;
int Game::clickY = 0;

bool Game::buyPressed = false;
bool Game::mortgagePressed = false;
bool Game::mousePressed = false;


int debounceDelay = 300;
int lastDebounce = 0;
std::string messageString;
int lastTurnToPressBuy = -1;

Game::Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen):tiles(40){
	mousePressed = false;
	turn = 0;
	int new_flag = 0;
	if (full_screen) {
		new_flag = SDL_WINDOW_FULLSCREEN;
	}
	if (TTF_Init() == -1) {
		std::cerr << "TTF init error \n";
		isRunning = false;
		return;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, x_pos, y_pos, width + 300, height, SDL_WINDOW_OPENGL);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		UserAnimator::attach(this);
		background = new Sprite("assets/board.bmp", width, height, 0, 0);
		if (!background)
			isRunning = false;
		background->setScale(100, 100);	
		this->screenWidth = width;
		this->screenHeight = height;
		dice = new Dice();
		dice->getFirstDieSprite()->setScale(width, height);
		dice->getSecondDieSprite()->setScale(width, height);
		players.push_back(new Player("Player 1", "assets/branza.bmp", START_X, START_Y, PAWN_SIZE + 3, PAWN_SIZE + 3));
		players[0]->setSpriteScale(width, height);
		players.push_back(new Player("Player 2", "assets/red.bmp", START_X + 1, START_Y -1, PAWN_SIZE, PAWN_SIZE));
		players[1]->setSpriteScale(width, height);
		/*
		players.push_back(new Player("Player 3", "assets/purple.bmp", 950, 930, PAWN_SIZE, PAWN_SIZE));
		players.push_back(new Player("Player 4", "assets/black.bmp", 960, 930, PAWN_SIZE, PAWN_SIZE));
		*/

		randomButtons.push_back(new Button("assets/buy_button0.bmp", "assets/buy_button0.bmp", 100, 5, 7, 5));
		randomButtons.push_back(new Button("assets/buy_button0.bmp", "assets/buy_button0.bmp", 107, 5, 7, 5));
		randomButtons.push_back(new Button("assets/buy_button0.bmp", "assets/buy_button0.bmp", 114, 5, 7, 5));
		randomButtons.push_back(new Button("assets/buy_button0.bmp", "assets/buy_button0.bmp", 121, 5, 7, 5));
		for (int i = 0; i < randomButtons.size(); i++)
			randomButtons[i]->getSprite()->setScale(width, height);

		buttons.push_back(new Button("assets/buy_button0.bmp", "assets/buy_button1.bmp", 107, 60, 22, 10));
		buttons.push_back(new Button("assets/sell_button0.bmp", "assets/sell_button1.bmp", 107, 70, 22, 10));
		buttons.push_back(new Button("assets/end_turn_button0.bmp", "assets/end_turn_button1.bmp", 107, 80, 22, 10));
 		for (int i = 0; i < buttons.size(); i++)
			buttons[i]->getSprite()->setScale(width, height);
		isRunning = true;
		fillTiles("assets/houseProperties.txt");
		menu = new Menu(this);
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

Dice* Game::getDice() {
	return dice;
}

 void Game::listen_event() {
	 menu->listen_event();
	 SDL_Event e;
	 
	 SDL_PollEvent(&e);
	 SDL_PumpEvents();
	 switch (e.type) {
	 case SDL_QUIT:
		 isRunning = false;
		 break;
	 case SDL_MOUSEBUTTONUP:
		 mousePressed = false;
		 break;
	 case SDL_MOUSEBUTTONDOWN: {
		 if (e.button.state == SDL_PRESSED && e.button.button == SDL_BUTTON_LEFT) {
			 if (!mousePressed) {
				 mousePressed = true;
				 clickX = e.button.x;
				 clickY = e.button.y;
				 std::cout << "Mouse X " << clickX << " Mouse Y :" << clickY << " \n";
				 lastDebounce = SDL_GetTicks();
				 if (dice->getFirstDieSprite()->isClicked() || dice->getSecondDieSprite()->isClicked()) {
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
								 if (!players[turn]->isJailed())
									 players[turn]->freeFromJail();
							 }
							 dice->setBlocked(true);
							 Game::nrDoublesThrown = 0;
						 }
						 else {
							 if (dice->thrownDouble()) {
								 Game::nrDoublesThrown++;
							 }

							 if (Game::nrDoublesThrown == 3) {
								 players[turn]->setJailFlag();
								 players[turn]->goToJail();
								 dice->setBlocked(true); //Set the dice block so while the current player is moving nobody can run the dice;
							 }
							 else {
								 players[turn]->setRemainingSteps(dice->getFirstDieValue() + dice->getSecondDieValue());

								 /*			DEBUG
								 /**/
								 //players[turn]->setRemainingSteps(1);

								 dice->setBlocked(true);
								 if (!dice->thrownDouble()) {
									 dice->setBlocked(true);
									 Game::nrDoublesThrown = 0;
								 }
							 }
						 }
					 }
				 }
				 else if (buttons[0]->getSprite()->isClicked()) {
					 if (!dice->isBlocked()) {
						 messageString = "You must roll the dice first!";
						 UserAnimator::popUpMessage(messageString);
					 }
					 else {
						 std::cout << "button0" << std::endl;
						 this->setBuyPressed(true);
						 if (lastTurnToPressBuy != turn) {
							 tiles[players[turn]->getCurrentPosition()]->getMeAnOwner(players[turn]); //tiles[1]->getMeAnOwner(players[turn]);
							 lastTurnToPressBuy = turn;
						 }
						 else
							 std::cout << "BUY WAS ALREADY PRESSED";
						 this->setBuyPressed(false);
					 }
				 }
				 else if (buttons[1]->getSprite()->isClicked()){
					 this->setMortgagePressed(true);
					 std::cout << "button1" << std::endl;
					 dynamic_cast<HouseProperty*>(tiles[8])->mortgage(players[turn]);
				 }
				 else if (buttons[2]->getSprite()->isClicked()) {

					 if (!(players[turn]->getFlag() == BUYER_TRADE || players[turn]->getFlag() == OWNER_TRADE)) {
						 lastTurnToPressBuy = turn;
						 turn++;
						 turn %= 2;
						 dice->setBlocked(false);
						 this->setBuyPressed(false);
						 this->setMortgagePressed(false);
						 UserAnimator::fadePropertyCard(tiles[players[turn]->getCurrentPosition()]);
						 std::cout << "button2" << std::endl;
					 }
					 else {
						 messageString = "You must finish the trade before ending your turn !";
						 UserAnimator::popUpMessage(messageString);
					 }
				 }
				 else if (randomButtons[0]->getSprite()->isClicked()) {
					 std::cout << "Am apasat butonul asta";
					 menu->setCurrentPage(0);
				 }
				 else if (randomButtons[1]->getSprite()->isClicked()) {
					 std::cout << "Am apasat butonul asta";
					 menu->setCurrentPage(1);
				 }
				 else if (randomButtons[2]->getSprite()->isClicked()) {
					 std::cout << "Am apasat butonul asta";
					 menu->setCurrentPage(2);
				 }
				 else if (randomButtons[3]->getSprite()->isClicked()) {
					 std::cout << "Am apasat butonul asta";
					 menu->setCurrentPage(3);
				 }
			 }
			 mousePressed = true;
		 }
		 else
			 mousePressed = false;
		}
		break;
	 }
 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 background->render();
	 for (int i = 0; i < PROP_NUM; i++) {
		 tiles[propIdx[i]]->render();
	 }
	 for (int i = 0; i < players.size(); i++)
		 players[i]->render();
	
	 for (int i = 0; i < buttons.size(); i++)
		 buttons[i]->render();

	 for (int i = 0; i < randomButtons.size(); i++)
		 randomButtons[i]->render();

	 dice->render();
	 menu->render();
	 UserAnimator::render();
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	 SDL_GetMouseState(&mouseX, &mouseY);
	 for (int i = 0; i < players.size(); i++) {
		 players[i]->update();

		 /*
		 Daca la iteratia curenta a Game::update() playerul a carui de la tura curent terminat sa de mutat ,i.e. remainingSteps == 0,
		 Vedem in functie de flagType ul pe care il avea setat ce se intampla cu el
		 */

		 if (i == turn && players[turn]->finishedMoving()) {
			 switch (players[turn]->getFlag()) {
			 case DICE_MOVE:
				 tiles[players[turn]->getCurrentPosition()]->doEffect(players[turn]);
				 break;
			 case MUST_BE_JAILED:
				 players[turn]->goToJail();
				 break;
			 case EXEC_COMMAND:
				 std::cout << players[turn]->getName() << " finished the command." << std::endl;
				 /*Dupa ce termina command, reintra in starea de "Sunt gata sa mut dupa cum zice zarul"*/

				 if (players[turn]->getCurrentPosition() == 28 || players[turn]->getCurrentPosition() == 12) {
					 if (dynamic_cast<UtilityProperty*>(tiles[players[turn]->getCurrentPosition()])->getOwner() != NULL
						 && !players[turn]->isBankrupt()) {
						 std::cout << players[turn]->getName() << " has to pay something\n";
						 dynamic_cast<UtilityProperty*>(tiles[players[turn]->getCurrentPosition()])->getOwner()->receiveMoney(dice->getFirstDieValue() + dice->getSecondDieValue() * 10);
						 players[turn]->payMoney(dice->getFirstDieValue() + dice->getSecondDieValue() * 10);
					 }
					 else
						 tiles[players[turn]->getCurrentPosition()]->doEffect(players[turn]);
				 }
				 else
					tiles[players[turn]->getCurrentPosition()]->doEffect(players[turn]);
				 players[turn]->setDiceFlag();
				 break;
			 case BUYER_TRADE:
				 if (players[turn]->onGoingTrade())
					 players[turn]->proposeSumFor(tiles[players[turn]->getCurrentPosition()]);
				 else {
					 players[turn]->buyProperty(tiles[players[turn]->getCurrentPosition()], true);
					 players[turn]->setDiceFlag();
				 }
				 break;
			
			 }
		  }

	 }
	 
	 for (int i = 0; i < buttons.size(); i++) {
		 buttons[i]->update(mouseX, mouseY);
	 }
	 
	 dice->update();
	 UserAnimator::update();
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
	 int buyPrice, updateCost, rentStages,mortgage;
	 std::vector<int>rentPrices(UPPER_RENTS_BOUND);	//dirty technique, but what can you do  `\ (' - ') /`
	 Groups color;
	 tiles[4] = new CommandTile("Income Tax");
	 tiles[38] = new CommandTile("Luxury Tax");
	 for (int i = 0; i < tiles.size(); i++) {
		 //For HouseProperty
		 if (pid < PROP_NUM  && i == propIdx[pid]) {
			 fin >> name >> buyPrice >> updateCost >> mortgage >> groupID;
			 name = parse(name, '_');
			 color = getGroupId(groupID);
			 rentStages = 6;
			 for (int i = 0; i < rentStages; i++)
				 fin >> rentPrices[i];
			 tiles[i] = new HouseProperty(name, buyPrice,updateCost,mortgage,rentPrices,color,i);
		
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

 Menu* Game::getMenu() {
	 return menu;
 }