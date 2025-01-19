#pragma once
#include "../Game.h"

class TextLabel {
private:
	SDL_Rect labelRect;
	SDL_Texture* labelTexture;
	TTF_Font* font = TTF_OpenFont("fonts/Branda-yolq.ttf", 24);
	SDL_Color textColor = { 0, 0, 0, 255 };
	bool isRect = true;

	std::string text;

public:
	TextLabel();
	TextLabel(const std::string& text);
	~TextLabel();
	void changeSize(int size);
	void setPosition(int xpos, int ypos);
	void renderLabel();
	void setText(const std::string& text);
	std::string getText();
	void noRect();
	void changeFont(const char* path, int size);
	void changeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

};