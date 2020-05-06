#include "../headers/Button.h"
#include "../headers/TextureMaker.h"
Button::Button(const char* filepath, int unitX, int unitY, int unitW, int unitH) {
	sprite = new Sprite(filepath, unitW, unitH, unitX, unitY);
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
		mouseY > sprite->pixelY()&&
		mouseY < sprite->pixelY() + sprite->pixelH())
			return true;
	return false;
}
