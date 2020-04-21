#define PAWN_SIZE 25
#define NUMBER_OF_PLAYERS 4
#include "../headers/Game.h"

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

