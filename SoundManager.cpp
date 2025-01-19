#include "SoundManager.h"
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
#include <thread>

SoundManager::SoundManager() : initialized(false) {}

SoundManager::~SoundManager() {
    if (initialized) {
        Mix_CloseAudio();
    }
}

void SoundManager::initialize() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    initialized = true;
}

void SoundManager::playSoundEffect(const std::string& soundFilePath, int flag) {
    if (!initialized) {
        std::cout << "SoundManager is not initialized!" << std::endl;
        return;
    }

    Mix_Chunk* soundEffect = Mix_LoadWAV(soundFilePath.c_str());
    if (!soundEffect) {
        std::cout << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        return;
    }

    int channel = Mix_PlayChannel(-1, soundEffect, flag);

    if (channel == -1) {
        std::cout << "Mix_PlayChannelTimed Error: " << Mix_GetError() << std::endl;
    }

}