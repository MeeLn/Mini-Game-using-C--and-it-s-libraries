#pragma once
#include "../Game.h"


class Button {
private:
	SDL_Texture* buttonTexture;
	bool buttoncolor = false;
	SDL_Rect buttonRect;
	TTF_Font* font = TTF_OpenFont("fonts/Branda-yolq.ttf", 24);
	SDL_Color textColor = { 0, 0, 255, 255 };

	std::string text;

public:
	Button(const std::string& text);
	~Button();
	void setPosition(int xpos, int ypos);
	void renderButton();
	void buttonController(SDL_Event& event);
	void setText(const std::string& text);
	std::string getText();
	void changeSize(int size);
	void changeFont(const char* path, int size);

	bool buttonClicked = false;
};