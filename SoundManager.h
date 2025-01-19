#pragma once
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void initialize();
    void playSoundEffect(const std::string& soundFilePath, int flag);

private:
    bool initialized;
};