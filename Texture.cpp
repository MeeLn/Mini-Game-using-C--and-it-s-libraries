#include "Texture.h"

SDL_Texture* Texture::LoadTexture(const char* filename) {
	SDL_Texture* tex;
	SDL_Surface* tempSurface = IMG_Load(filename);
	tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void Texture::Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect desRect) {
	SDL_RenderCopy(Game::renderer, tex, &srcRect, &desRect);
}