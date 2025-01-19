#include "TextField.h"

TextField::TextField(SDL_Renderer* renderer, const std::string& Text) {
    textSurface = TTF_RenderText_Blended(font, Text.c_str(), textColor);
    text = Text.c_str();
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    isEditing = false;
}

TextField::~TextField()
{
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void TextField::setPosition(int xpos, int ypos, int width, int height) {
    Rect.x = xpos;
    Rect.y = ypos;
    Rect.w = width;
    Rect.h = height;
}

void TextField::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_TEXTINPUT && isEditing) {
        text += event.text.text;
        updateTextTexture(Game::renderer);
    }
    else if (event.type == SDL_KEYDOWN && isEditing) {

        toggleCursorVisibility();
        if (event.key.keysym.sym == SDLK_BACKSPACE && !text.empty()) {

            text.pop_back();
            updateTextTexture(Game::renderer);
        }
        else if (event.key.keysym.sym == SDLK_RETURN) {
            isEditing = false;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= Rect.x && mouseX <= Rect.x + Rect.w &&
            mouseY >= Rect.y && mouseY <= Rect.y + Rect.h)
        {
            isEditing = true;
        }
        else {
            isEditing = false;
        }
    }
}

void TextField::render(SDL_Renderer* renderer)
{

    SDL_SetRenderDrawColor(renderer, 5, 5, 5, 255);
    SDL_RenderFillRect(renderer, &Rect);
    if (isEditing) {
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderFillRect(renderer, &Rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &Rect);

    int cursorX;
    int cursorY;
    int cursorHeight;

    // Render the text
    if (textSurface) {
        textRect = { Rect.x + 5, Rect.y + 5, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        // Render the text cursor if the cursor is visible
        if (isEditing && showCursor)
        {
            // Determine the cursor position based on the current text length
            cursorX = textRect.x + textSurface->w + 1;
            cursorY = textRect.y;
            cursorHeight = TTF_FontHeight(font) - 2;

            // Draw the cursor as a vertical line
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect cursorRect = { cursorX, cursorY, 2, cursorHeight };
            SDL_RenderFillRect(renderer, &cursorRect);
        }
    }
    else {
        if (isEditing && showCursor)
        {
            cursorX = textRect.x + 1;
            cursorY = textRect.y;
            cursorHeight = TTF_FontHeight(font) - 2;

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect cursorRect = { cursorX, cursorY, 2, cursorHeight };
            SDL_RenderFillRect(renderer, &cursorRect);
        }
    }
}

std::string TextField::getText() const
{
    return text;
}

void TextField::updateTextTexture(SDL_Renderer* renderer)
{
    if (renderer)
    {
        SDL_FreeSurface(textSurface);
        textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        SDL_DestroyTexture(textTexture);
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    }
}

void TextField::toggleCursorVisibility() {
    showCursor = !showCursor;
}

void TextField::blinkCursor() {
    blinkState = !blinkState;
    if (blinkState)
    {
        toggleCursorVisibility();
    }
}

void TextField::changeFont(const char* path, int size) {
    font = TTF_OpenFont(path, size);
    if (size == NULL) {
        font = TTF_OpenFont(path, 24);
    }
}