#include "../headers/Button.h"

Button::Button(const char* filepath, int x, int y, int w, int h) {
	buttonFrame.x = x;
	buttonFrame.y = y;
	buttonFrame.w = w;
	buttonFrame.h = h;
	buttonTexture = TextureMaker::textureFromBMP(filepath);
}
Button::~Button() {

}
void Button::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonFrame);
}

SDL_Rect Button::getButtonFrame()
{
	return buttonFrame;
}

SDL_Texture* Button::getButtonTexture()
{
	return buttonTexture;
}

bool Button::hoverButton(int mouseX, int mouseY)
{
	if (mouseX > this->getButtonFrame().x &&
		mouseX < this->getButtonFrame().x + this->getButtonFrame().w &&
		mouseY > this->getButtonFrame().y &&
		mouseY < this->getButtonFrame().y + this->getButtonFrame().h)
			return true;
	return false;
}
