#pragma once
#include "Game.h"
#include "Vector2D.h"

class ColliderObject {
private:
	SDL_Texture* texture;
	int scale;

public:
	ColliderObject();
	ColliderObject(int id, int x, int y, int h, int w, int sc);
	~ColliderObject();
	void update();
	void render();
	void render(int offsetX, int offsetY);

	int id;
	Vector2D position;
	SDL_Rect srcRect, desRect;
};
