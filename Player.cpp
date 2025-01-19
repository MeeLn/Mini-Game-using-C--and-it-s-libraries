#include "Player.h"
#include "Texture.h"
#include "SoundManager.h"

SoundManager Manager;

Player::Player(int id, int x, int y) {

	Manager.initialize();

	const char* filename = NULL;
	this->id = id;
	switch (id)
	{
	case 0:
		filename = "assets/box1.png";
		break;
	case 1:
		filename = "assets/box.png";
		break;
	case 2:
		filename = "assets/box2.png";
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
	velocity.zero();
}

void Player::changed(const char* filename) {
	texture = Texture::LoadTexture(filename);
}


Player::Player() {
	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;
	desRect.h = srcRect.h * 2;
	desRect.w = srcRect.w * 2;
	desRect.x = desRect.y = 0;
}

Player::~Player() {

}

void Player::update() {

	position.x += velocity.x * speed;
	position.y += velocity.y * flipSpeed;

	desRect.x = position.x;
	desRect.y = position.y;

}

void Player::render() {
	Texture::Draw(texture, srcRect, desRect);
}

void Player::render(int offsetX, int offsetY) {
	SDL_Rect renderQuad = { desRect.x + offsetX, desRect.y + offsetY, desRect.w, desRect.h };
	SDL_RenderCopy(Game::renderer, texture, NULL, &renderQuad);
}

void Player::KeyboardController() {
	switch (Game::event.type) {
	case SDL_KEYDOWN:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_UP:
			if (!isFlip) {
				Manager.playSoundEffect("sounds/flip.wav", 0);
				counter = true;
				isFlip = true;
				velocity.y = -2;
			}
			break;
		case SDLK_DOWN:
			if (isFlip) {
				Manager.playSoundEffect("sounds/flip.wav", 0);
				isFlip = false;
				velocity.y = 2;
				counter = false;
			}
			break;
		case SDLK_RIGHT:
			velocity.x = 1;
			break;
		case SDLK_LEFT:
			velocity.x = -1;
			break;
		case SDLK_SPACE:


			Manager.playSoundEffect("sounds/jump_main.wav", 0);
			isJumping = true;
			if (isJumping && position.y != 512 - jumpHeight) {
				velocity.y = -(jumpSpeed);
			}
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_UP:
			
			break;
		case SDLK_DOWN:
			
			break;
		case SDLK_RIGHT:
			velocity.x = 0;
			break;
		case SDLK_LEFT:
			velocity.x = -0;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}