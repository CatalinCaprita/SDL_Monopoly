#include "../headers/Button.h"
#include "../headers/TextureMaker.h"
Button::Button(const char* filePathNormal, const char* filePathHover, const char* filePathClicked, int unitX, int unitY, int unitW, int unitH, ButtonState buttonState) {
	sprite = new Sprite(filePathNormal, unitW, unitH, unitX, unitY);
	spriteNormal = new Sprite(filePathNormal, unitW, unitH, unitX, unitY);
	spriteHover = new Sprite(filePathHover, unitW, unitH, unitX, unitY);
	spriteClicked = new Sprite(filePathClicked, unitW, unitH, unitX, unitY);
	this->buttonState = buttonState;
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
	if (hoverButton(mouseX, mouseY)) // 
		if (sprite->isClicked()) // if mouse hovers over button & if clicked
			buttonState = CLICKED;
		else
			buttonState = HOVER; // if mouse hovers & not clicked
	else
		buttonState = NORMAL;
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
	}
			
}
