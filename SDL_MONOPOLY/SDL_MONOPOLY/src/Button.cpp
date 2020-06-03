#include "../headers/Button.h"
#include "../headers/TextureMaker.h"
Button::Button(const char* filepathNormal, const char* filepathHover, int unitX, int unitY, int unitW, int unitH, ButtonState buttonState) {
	sprite = new Sprite(filepathNormal, unitW, unitH, unitX, unitY);
	spriteHover = new Sprite(filepathHover, unitW, unitH, unitX, unitY);
	spriteNormal = new Sprite(filepathNormal, unitW, unitH, unitX, unitY);
	this->buttonState = buttonState;
}
Button::~Button() {

}
Sprite* Button::getSprite() {
	return sprite;
}
void Button::render() {
	if (buttonState == HOVER) {
		sprite->render();
	}
	else if (buttonState == NORMAL) {
		sprite->render();
	}
}

bool Button::hoverButton(int mouseX, int mouseY)
{
	if (mouseX > sprite->pixelX() &&
		mouseX < sprite->pixelX() + sprite->pixelW() &&
		mouseY > sprite->pixelY()&&
		mouseY < sprite->pixelY() + sprite->pixelH())
			return true;
	return false;
}


void Button::update(int mouseX, int mouseY) {
	
	if (hoverButton(mouseX, mouseY) && sprite != spriteHover) {
		buttonState = HOVER;
		sprite->setTexture(spriteHover->getTexture());
		//std::cout << "HOVER\n";
	}
	else if(!hoverButton(mouseX, mouseY) && sprite != spriteNormal) {

		buttonState = NORMAL;
		sprite->setTexture(spriteNormal->getTexture());
		//std::cout << "NORMAL\n";
	}
	
	
}
