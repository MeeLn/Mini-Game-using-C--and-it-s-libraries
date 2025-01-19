#include "Button.h"

Button::Button(const std::string& text) {
    this->text = text;
}

Button::~Button() {
    SDL_DestroyTexture(buttonTexture);
    TTF_CloseFont(font);
}

void Button::setPosition(int xpos, int ypos) {
    buttonRect.x = xpos;
    buttonRect.y = ypos;
}

void Button::renderButton() {

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    buttonTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_QueryTexture(buttonTexture, nullptr, nullptr, &buttonRect.w, &buttonRect.h);
    SDL_FreeSurface(surface);


    SDL_Rect Rect = { buttonRect.x - 2, buttonRect.y - 2, buttonRect.w + 4, buttonRect.h + 4 };

    if (buttoncolor) {
        SDL_SetRenderDrawColor(Game::renderer, 255, 51, 0, 12);
        SDL_RenderFillRect(Game::renderer, &Rect);
    }
    else {
        SDL_SetRenderDrawColor(Game::renderer, 5, 5, 5, 255);
        SDL_RenderFillRect(Game::renderer, &Rect);

        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
        SDL_RenderDrawRect(Game::renderer, &Rect);
    }
    if (buttoncolor)
        buttoncolor = false;

    SDL_RenderCopy(Game::renderer, buttonTexture, nullptr, &buttonRect);
    SDL_Delay(50);
}

void Button::buttonController(SDL_Event& event) {
    switch (event.type) {
    case SDL_QUIT:
        SDL_Quit();
        exit(0);
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT &&
            event.button.x >= buttonRect.x && event.button.x <= buttonRect.x + buttonRect.w &&
            event.button.y >= buttonRect.y && event.button.y <= buttonRect.y + buttonRect.h)
        {
            buttonClicked = true;
            buttoncolor = true;
        }
        break;
    }
}

std::string Button::getText() {
    return text;
}

void Button::changeSize(int size) {
    font = TTF_OpenFont("fonts/Branda-yolq.ttf", size);
}

void Button::setText(const std::string& text) {
    this->text = text;
}

void Button::changeFont(const char* path, int size) {
    font = TTF_OpenFont(path, size);
    if (size == NULL) {
        font = TTF_OpenFont(path, 24);
    }
}