#define PAWN_SIZE 25
#include "../headers/Game.h"

Game::Game(const char* title, int x_pos, int y_pos, int width, int height, bool full_screen) {
	int new_flag = 0;
	if (full_screen) {
		new_flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, new_flag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
		TextureMaker::attach(renderer);
		background = TextureMaker::textureFromBMP("assets/background.bmp");
		spriteFrame.x = 0;
		spriteFrame.y = 0;
		spriteFrame.w = 1000;
		spriteFrame.h = 1000;

		if (!background || !playerTexture)
			isRunning = false;
		player1 = new Player("Player1", "assets/blue.bmp", 930, 930, PAWN_SIZE, PAWN_SIZE);
		player2 = new Player("Player2", "assets/red.bmp", 940, 930, PAWN_SIZE, PAWN_SIZE);
		player3 = new Player("Player3", "assets/purple.bmp", 950, 930, PAWN_SIZE, PAWN_SIZE);
		player4 = new Player("Player4", "assets/black.bmp", 960, 930, PAWN_SIZE, PAWN_SIZE);
		dice = new Dice();
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
	 SDL_PollEvent(&e);

	 if(e.type == SDL_QUIT)
		 isRunning = false;

	 const Uint8* state = SDL_GetKeyboardState(NULL);
	 if (state[SDL_SCANCODE_Q]) {
		 player1->move();
	 }
	 if (state[SDL_SCANCODE_W]) {
		 player2->move();
	 }
	 if (state[SDL_SCANCODE_E]) {
		 player3->move();
	 }
	 if (state[SDL_SCANCODE_R]) {
		 dice->roll(renderer);
		 for (int i = 0; i < dice->getFirstDieValue() + dice->getSecondDieValue(); i++) {
			 player4->move();
			 player4->update();
			 Game::render();
			 SDL_RenderPresent(renderer);
			 SDL_Delay(500);
		 }
		 // TO DO -> Move the code in  Player::move() because it looks like absolute garbage, it still will, but less
	 }
	 
 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 SDL_RenderCopy(renderer, background, NULL, &spriteFrame);
	 player1->render(renderer);
	 player2->render(renderer);
	 player3->render(renderer);
	 player4->render(renderer);
	 dice->render(renderer);
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	player1->update();
	player2->update();
	player3->update();
	player4->update();
	dice->update();
 }

