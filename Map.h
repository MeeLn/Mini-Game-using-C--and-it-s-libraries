#pragma once
#include "Texture.h"
#include<string>

class Map
{
private:
	SDL_Texture* air;
	SDL_Texture* cloud;
	SDL_Texture* upground;
	SDL_Texture* downground;

	SDL_Rect srcRect, desRect;

public:
	Map();
	~Map();
	void LoadMap(std::string path);
	void Draw();
	void Draw(int offsetX, int offsetY);

	int i = 1, j = 6;
	int mapTile[29][224];
};