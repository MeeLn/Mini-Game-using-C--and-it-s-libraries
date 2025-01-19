#pragma once
#include "Game.h"
#include "Vector2D.h"

class Player {
private:
	SDL_Texture* texture;

public:
	Player();
	Player(int id, int x, int y);
	~Player();
	void update();
	void render();
	void render(int offsetX, int offsetY);
	void KeyboardController();
	void changed(const char* filename);

	int id;
	bool counter = false;
	bool isFlip = false;
	bool isMoving = false;
	bool isJumping = false;
	int speed = 4;
	int jumpHeight = 120;
	int jumpSpeed = 2;
	int flipSpeed = 4;
	int distance,StickDistance = 100;
	Vector2D position;
	Vector2D velocity;
	SDL_Rect srcRect, desRect;
	std::string name;
	int score=0, health =2;
};