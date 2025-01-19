#pragma once
#include "Game.h"
#include "Vector2D.h"

class GameObject {
private:
	SDL_Texture* texture;

public:
	GameObject();
	GameObject(int id, int x, int y);
	~GameObject();
	void LoadObject(int id, int x, int y);
	void changePosition(int x, int y);
	void update();
	void render();
	void render(int offsetX, int offsetY);

	int id;
	Vector2D position;
	SDL_Rect srcRect, desRect;
};