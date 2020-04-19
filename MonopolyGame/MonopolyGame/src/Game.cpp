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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		TextureMaker::attach(renderer);
		background = TextureMaker::textureFromBMP("assets/background.bmp");
		if (!background || !playerTexture)
			isRunning = false;
		std::vector<Tile*> t1;
		std::vector<Tile*> t2;
		player1 = new Player(t1, "Player1", "assets/blue.bmp", 930, 930, 30, 30);
		player2 = new Player(t2, "Player1", "assets/red.bmp", 940, 930, 30, 30);
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
		 player1->move(1);
	 }
	 if (state[SDL_SCANCODE_W]) {
		 player2->move(1);
	 }
	 
 }
 void Game::render() {
	 SDL_RenderClear(renderer);
	 SDL_RenderCopy(renderer, background, NULL, NULL);
	 player1->render(renderer);
	 player2->render(renderer);
	 SDL_RenderPresent(renderer);
}

 void Game::update() {
	player1->update();
	player2->update();
 }

