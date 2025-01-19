#pragma once
#include "../Game.h"

class TextField {
public:
    TextField(SDL_Renderer* renderer, const std::string& Text);
    ~TextField();
    void setPosition(int xpos, int ypos, int width, int height);
    void handleEvent(SDL_Event& event);
    void render(SDL_Renderer* renderer);
    std::string getText() const;
    void toggleCursorVisibility();
    void blinkCursor();
    void changeFont(const char* path, int size);

private:
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect Rect, textRect;
    std::string text;
    TTF_Font* font = TTF_OpenFont("./fonts/Branda-yolq.ttf", 24);
    SDL_Color textColor = { 0, 0, 255, 255 };

    bool showCursor = true;
    bool blinkState = true;
    bool isEditing;

    void updateTextTexture(SDL_Renderer* renderer);
};