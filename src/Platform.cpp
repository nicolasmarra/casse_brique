#include "Platform.h"

int Platform::getSpeed() const { return _speed; }

void Platform::setSpeed(int speed) { _speed = speed; }

void Platform::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);
    SDL_Rect rect = {getX(), getY(), getWidth(), getHeight()};
    SDL_RenderFillRect(renderer, &rect);
}