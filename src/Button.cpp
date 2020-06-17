#include "../headers/Button.h"
#include "../headers/TextureMaker.h"
Button::Button(const char* filePathNormal, const char* filePathHover, const char* filePathClicked, int unitX, int unitY, int unitW, int unitH, ButtonState buttonState) {
	
	graySprite = NULL; // ONLY FOR BUTTONS AT THE TOP OF MENU !!

	sprite = new Sprite(filePathNormal, unitW, unitH, unitX, unitY);
	spriteNormal = new Sprite(filePathNormal, unitW, unitH, unitX, unitY);
	spriteHover = new Sprite(filePathHover, unitW, unitH, unitX, unitY);
	spriteClicked = new Sprite(filePathClicked, unitW, unitH, unitX, unitY);
	this->buttonState = buttonState;

	graySpriteInit();
}
Button::~Button() {

}
Sprite* Button::getSprite() {
	return sprite;
}
void Button::render() {
	sprite->render();
}

bool Button::hoverButton(int mouseX, int mouseY)
{
	if (mouseX > sprite->pixelX() &&
		mouseX < sprite->pixelX() + sprite->pixelW() &&
		mouseY > sprite->pixelY() &&
		mouseY < sprite->pixelY() + sprite->pixelH())
			return true;
	return false;
}


void Button::updateButtonState(int mouseX, int mouseY) {
	if (buttonState != NOPLAYER) {
		if (hoverButton(mouseX, mouseY)) // 
			if (sprite->isClicked()) // if mouse hovers over button & if clicked
				buttonState = CLICKED;
			else
				buttonState = HOVER; // if mouse hovers & not clicked
		else
			buttonState = NORMAL;
	}
} // function that updates the current buttonState

void Button::update(int mouseX, int mouseY) {
	updateButtonState(mouseX, mouseY);
	switch (buttonState){
		case NORMAL:
			sprite->setTexture(spriteNormal->getTexture());
			break;
		case HOVER:
			sprite->setTexture(spriteHover->getTexture());
			break;
		case CLICKED:
			sprite->setTexture(spriteClicked->getTexture());
			break;
		case NOPLAYER:
			sprite->setTexture(graySprite->getTexture());
			break;
	}
			
}

ButtonState Button::getButtonState()
{
	return buttonState;
}


void Button::graySpriteInit() {
	char filepath[30] = "";

	if (spriteNormal != NULL)
	{
		if (strcmp(spriteNormal->getPath(), "assets/menu/car_button.bmp") == 0){
			strcpy_s(filepath, "assets/menu/car_button3.bmp");
		} else if (strcmp(spriteNormal->getPath(), "assets/menu/ship_button.bmp") == 0){
			strcpy_s(filepath, "assets/menu/ship_button3.bmp");
		} else if (strcmp(spriteNormal->getPath(), "assets/menu/plane_button.bmp") == 0) {
			strcpy_s(filepath, "assets/menu/plane_button3.bmp");
		} else if (strcmp(spriteNormal->getPath(), "assets/menu/train_button.bmp") == 0) {
			strcpy_s(filepath, "assets/menu/train_button3.bmp");
		}
	}
	if (filepath) {
		graySprite = new Sprite(filepath, sprite->unitW(), sprite->unitH(), sprite->unitX(), sprite->unitY());
	}
}


