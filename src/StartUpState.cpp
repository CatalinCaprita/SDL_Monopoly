#include "../headers/StartUpState.h"
#include "../headers/TextureMaker.h"
#include "../headers/Game.h"
#define MON_X 0
#define MON_Y 0
#define MON_W 20 
#define MON_H 26
#define BUBBLE_H 100
#define BUBBLE_W 80
#define LAB_X 21
#define LAB_Y 34
#define LAB_H 7
SDL_Color BLACK2 = { 0,0,0,0 };
int sw, sh;
StartUpState::StartUpState(int screenW,int screenH ):renderer(nullptr){
	isRunning = false;
	sw = screenW;
	sh = screenH;
	background = new Sprite("assets/start_up/start_board.bmp",screenW, screenH, 0, 0);
	if (!background)
		isRunning = false;
	background->setScale(100, 100);
	monMan = new Sprite("assets/start_up/mon_man_greet.bmp", MON_W, MON_H, MON_X, MON_Y, screenW, screenH, true);
	bubble = new Sprite("assets/start_up/start_bubble.bmp", BUBBLE_W, BUBBLE_H, MON_X, MON_Y , screenW, screenH, true);
	if (TTF_Init() == -1) {
		std::cerr << "TTF init error \n";
		isRunning = false;
		return;
	}
	std::string text = "Welcome To MONOMFMI! Let's get to know eachother first!";
	UILabel* u = new UILabel(LAB_X, LAB_Y, BUBBLE_W / 2, LAB_H, text, TTF_OpenFont("assets/fonts/prompt_std2.ttf", 60), BLACK2);
	u->setScale(screenW, screenH);
	u->setLabelTexture(screenW);
	labels.push_back(u);
	
	for (int i = 0; i < 4; i++) {
		text = "Player " + std::to_string(i) + "s name :";
		UILabel* u = new UILabel(LAB_X - 15, LAB_Y + (i + 1) * LAB_H, BUBBLE_W / 3, LAB_H - 3, text, TTF_OpenFont("assets/fonts/prompt_std2.ttf", 60), BLACK2);
		u->setScale(screenW, screenH);
		u->setLabelTexture(screenW);
		labels.push_back(u);
		std::string emptym = " ";
		TextBox* tb = new TextBox("assets/trade/trade_text_box.bmp", LAB_X - 15  + BUBBLE_W / 2 + 1, LAB_Y + (i + 1) * LAB_H,BUBBLE_W/3,LAB_H, emptym);
		tb->setScale(screenW, screenH);
		tbs.push_back(tb);

	}
	buttons.push_back(new Button("assets/start_up/start_button.bmp", "assets/start_up/start_button.bmp", "assets/start_up/start_button.bmp", LAB_X, 71, 20, 10));
	buttons.push_back(new Button("assets/start_up/exit_button.bmp", "assets/start_up/exit_button.bmp", "assets/start_up/exit_button.bmp", LAB_X + 30, 71, 20, 10));
	for (Button* b : buttons) {
		b->getSprite()->setScale(screenW, screenH);
	}

	renderer = GameStateManager::getInstance()->getRenderer();
	isRunning = true;

}

StartUpState::~StartUpState(){
	for (int i = buttons.size() - 1; i >= 0; i--) {
		delete buttons[i];
		buttons.erase(buttons.begin() + i);
	}
	for (int i = tbs.size() - 1; i >= 0; i--) {
		delete tbs[i];
		tbs.erase(tbs.begin() + i);
	}
	for (int i = labels.size() - 1; i >= 0; i--) {
		delete labels[i];
		labels.erase(labels.begin() + i);
	}
	delete monMan;
	delete bubble;
	delete background;
}

void StartUpState::listen_event(){
	SDL_Event e;
	SDL_StartTextInput();
	SDL_PollEvent(&e);
	SDL_PumpEvents();
	switch (e.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_BACKSPACE) {
			GameStateManager::getInstance()->setBackFlag(true);
		}
		else if (e.key.keysym.sym == SDLK_RETURN) {
			GameStateManager::getInstance()->setEnterFlag(true);
		}
		break;
	case SDL_TEXTINPUT:
		GameStateManager::getInstance()->setKeyStroke(true);
		GameStateManager::getInstance()->setInChar(e.text.text[0]);
		break;
	case SDL_MOUSEBUTTONUP:
		GameStateManager::getInstance()->setMousePressed(false);
		std::cout << "Mouse Set to false";
		break;
	case SDL_MOUSEBUTTONDOWN: {
		if (e.button.state == SDL_PRESSED && e.button.button == SDL_BUTTON_LEFT) {
			if (!GameStateManager::getInstance()->mouseClick()) {
				GameStateManager::getInstance()->setClickX(e.button.x);
				GameStateManager::getInstance()->setClickY(e.button.y);
				GameStateManager::getInstance()->setMousePressed(true);
				if (buttons[0]->getSprite()->isClicked()) {
					//Goes Onto an Adventureeeee I am so god  damn tired please do kill me omg i desaparas c0[J jcA|sc
					std::vector<std::string> pn;
					std::string name;
					for(int i=0; i < tbs.size(); i++){
						if (tbs[i]->getInput() != " " && tbs[i]->getInput() != "") {
							pn.push_back(tbs[i]->getInput());
						}
					}
					GameStateManager::getInstance()->popState();
					Game* play = new Game(sw, sh, pn);
					GameStateManager::getInstance()->pushState(play);
				}
			}
			else {
				GameStateManager::getInstance()->setMousePressed(false);
			}
		}
		break;
		}
	}
}

void StartUpState::update(){
	for (TextBox* tb : tbs) {
		tb->update();
	}
}

void StartUpState::render(){
	background->render();
	monMan->render();
	bubble->render();
	for (UILabel* lab : labels) {
		lab->render();
	}
	for (TextBox* tb : tbs) {
		tb->render();
	}
	for (Button* b : buttons) {
		b->render();
	}
	SDL_RenderPresent(renderer);
}

bool StartUpState::running()
{
	return isRunning;
}
