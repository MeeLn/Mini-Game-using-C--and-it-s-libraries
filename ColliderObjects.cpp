#include "ColliderObject.h"
#include "Texture.h"

ColliderObject::ColliderObject(int id, int x, int y, int h, int w, int sc) {
	this->id = id;
	const char* filename = NULL;
	switch (id)
	{
	case 0:
		filename = "assets/wall.png";
		break;
	case 1:
		filename = "assets/wall1.png";
		break;
	case 2:
		filename = "assets/finish.png";
		break;
	default:
		break;
	}

	texture = Texture::LoadTexture(filename);

	position.x = x;
	position.y = y;
	scale = sc;

	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = h;
	desRect.w = w;
	desRect.x = position.x;
	desRect.y = position.y;
}

ColliderObject::ColliderObject() {
	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = srcRect.h * scale;
	desRect.w = srcRect.w * scale;
	desRect.x = desRect.y = 0;
}

ColliderObject::~ColliderObject() {

}

void ColliderObject::update() {

	desRect.x = position.x;
	desRect.y = position.y;

}

void ColliderObject::render() {
	Texture::Draw(texture, srcRect, desRect);
}

void ColliderObject::render(int offsetX, int offsetY) {
	SDL_Rect renderQuad = { desRect.x + offsetX, desRect.y + offsetY, desRect.w, desRect.h };
	SDL_RenderCopy(Game::renderer, texture, NULL, &renderQuad);
}