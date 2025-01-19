#pragma once
#include "SDL.h"
#include "Player.h"
#include "ColliderObject.h"
#include "GameObject.h"

class Collision {
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};