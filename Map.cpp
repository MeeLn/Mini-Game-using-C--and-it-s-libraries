#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map() {

	for (int row = 0; row < 29; row++) {
		for (int col = 0; col < 224; col++) {
			mapTile[row][col] = 0;
		}
	}

	air = Texture::LoadTexture("assets/fullyboxed.png");
	cloud = Texture::LoadTexture("assets/fullyboxed.png");
	upground = Texture::LoadTexture("assets/boxed.png");
	downground = Texture::LoadTexture("assets/boxed.png");

	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = srcRect.h ;
	desRect.w = srcRect.w ;
	desRect.x = desRect.y = 0;

}

Map::~Map()
{
}

void Map::LoadMap(std::string path) {
	char tile = NULL;
	
	std::fstream mapFile;
	mapFile.open(path);

	for (int row = 0; row < 29; row++) {
		for (int col = 0; col < 224; col++) {
			mapFile.get(tile);

			mapTile[row][col] =atoi(&tile);
				
			mapFile.ignore();
		}
	}
	mapFile.close();
	//std::cout << "Map Loaded!!" << std::endl;
}

void Map::Draw() {
	for (int row = i; row < 29; row++) {
		for (int col = j; col < 224; col++) {
			desRect.x = col * 32;
			desRect.y = row * 32;
			switch (this->mapTile[row][col])
			{
			case 0:
				Texture::Draw(air, srcRect, desRect);
				break;
			case 1:
				Texture::Draw(upground, srcRect, desRect);
				break;
			case 2:
				Texture::Draw(downground, srcRect, desRect);
				break;
			case 3:
				Texture::Draw(cloud, srcRect, desRect);
				break;
			default:
				break;
			}
		}
	}
}

void Map::Draw(int offsetX, int offsetY) {
	for (int row = i; row < 29; row++) {
		for (int col = j; col < 224; col++) {
			desRect.x = col * 32 + offsetX;
			desRect.y = row * 32 + offsetY;
			switch (this->mapTile[row][col]) {
			case 0:
				Texture::Draw(air, srcRect, desRect);
				break;
			case 1:
				Texture::Draw(upground, srcRect, desRect);
				break;
			case 2:
				Texture::Draw(downground, srcRect, desRect);
				break;
			case 3:
				Texture::Draw(cloud, srcRect, desRect);
				break;
			default:
				break;
			}
		}
	}
}