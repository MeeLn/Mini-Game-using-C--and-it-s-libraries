#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject(int id, int x, int y) {
	const char* filename = NULL;
	this->id = id;
	switch (id)
	{
	case 0:
		filename = "assets/invertedspikes.png";
		break;
	case 1:
		filename = "assets/spikes.png";
		break;
	default:
		break;
	}
	texture = Texture::LoadTexture(filename);

	position.x = x;
	position.y = y;

	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = srcRect.h * 2;
	desRect.w = srcRect.w * 2;
	desRect.x = position.x;
	desRect.y = position.y;
}

void GameObject::LoadObject(int id, int x, int y) {
	const char* filename = NULL;
	this->id = id;
	switch (id)
	{
	case 0:
		filename = "assets/invertedspikes.png";
		break;
	case 1:
		filename = "assets/spikes.png";
		break;
	case 2:
		filename = "assets/evilbox.png";
		break;
	default:
		break;
	}
	texture = Texture::LoadTexture(filename);

	position.x = x;
	position.y = y;

	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = srcRect.h * 2;
	desRect.w = srcRect.w * 2;
	desRect.x = position.x;
	desRect.y = position.y;
}

void GameObject::changePosition(int x, int y) {
	position.x = x;
	position.y = y;
}

GameObject::GameObject() {
	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = srcRect.h * 2;
	desRect.w = srcRect.w * 2;
	desRect.x = desRect.y = 0;
}

GameObject::~GameObject() {

}

void GameObject::update() {

	desRect.x = position.x;
	desRect.y = position.y;

}

void GameObject::render() {
	Texture::Draw(texture, srcRect, desRect);
}

void GameObject::render(int offsetX, int offsetY) {
	SDL_Rect renderQuad = { desRect.x + offsetX, desRect.y + offsetY, desRect.w, desRect.h };
	SDL_RenderCopy(Game::renderer, texture, NULL, &renderQuad);
}