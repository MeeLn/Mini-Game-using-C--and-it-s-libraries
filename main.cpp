#define _CRTDBG_MAP_ALLOC
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Game.h"
#include "SoundManager.h"
#include <Windows.h>
#include <crtdbg.h>

SoundManager back;
Game* game = nullptr;
int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int FrameRate = 60;
	int FrameDelay = 1000 / FrameRate;
	Uint32 FrameStart;
	int FrameTime;

	game = new Game();
	back.initialize();

	game->Init("DashLeapster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	back.playSoundEffect("sounds/back3.wav", -1);

	while (game->running()) {
		FrameStart = SDL_GetTicks();
		game->handleEvent();
		game->update();
		game->render();
		FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime) {
			SDL_Delay(FrameDelay - FrameTime);
		}
	}
	game->clean();
	
	return 0;
}