#include "TextLabel.h"

TextLabel::TextLabel() {

}

TextLabel::TextLabel(const std::string& text) {
    this->text = text;
}

TextLabel::~TextLabel() {
    SDL_DestroyTexture(labelTexture);
    TTF_CloseFont(font);
}

void TextLabel::setPosition(int xpos, int ypos) {
    labelRect.x = xpos;
    labelRect.y = ypos;
}

void TextLabel::renderLabel() {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelRect.w, &labelRect.h);
    SDL_FreeSurface(surface);


    if (isRect) {
        SDL_Rect Rect = { labelRect.x - 2, labelRect.y - 2, labelRect.w + 4, labelRect.h + 4 };
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(Game::renderer, &Rect);
    }

    SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &labelRect);
}


void TextLabel::setText(const std::string& text) {
    this->text = text;
}

std::string TextLabel::getText() {
    return text;
}

void TextLabel::changeSize(int size) {
    font = TTF_OpenFont("fonts/Branda-yolq.ttf", size);
}

void TextLabel::noRect() {
    isRect = false;
}

void TextLabel::changeFont(const char* path, int size) {
    font = TTF_OpenFont(path, size);
    if (size == NULL) {
        font = TTF_OpenFont(path, 24);
    }
}

void TextLabel::changeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    textColor = { red, green, blue, alpha };
}