#pragma once
#include "SDL.h"
#include<iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

class Game
{
private:
	bool isRunning;

	SDL_Window* window;

	int cameraX = 0;
	int cameraY = 0;
	int count = 0;

public:
	Game();
	~Game();
	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvent();
	void update();
	void render();
	void clean();
	bool running();
	void collisionHandler();
	void resetGame();
	void generateRandom();

	static SDL_Renderer* renderer;
	static SDL_Event event;

	int Time = 0, checkTime;
	bool isMoving, start, end, check, timer,speedFlag;
	int previousScore = 0, prevscore=0;
	int randomNumbers[5];
	int threeDups = -1, twoDups[2] = { -1,-1 };
	bool hasTwoDuplicates = false;
	bool hasThreeDuplicates = false;

};