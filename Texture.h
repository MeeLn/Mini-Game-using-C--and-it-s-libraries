#pragma once
#include "Game.h"

class Texture {
public:
	static SDL_Texture* LoadTexture(const char* file_name);
	static void Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect desRect);
};