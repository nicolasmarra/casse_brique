#include "Platform.h"

int Platform::getSpeed() const { return _speed; }

void Platform::setSpeed(int speed) { _speed = speed; }

void Platform::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);

    SDL_Rect rect = {(int)(getX()), (int)getY(), (int)getWidth(),
                     (int)getHeight()};
    SDL_RenderFillRect(renderer, &rect);
}

void Platform::move(int direction, int windowWidth) {
    if (direction == 1) {
        if (getX() + getWidth() < windowWidth) {
            setX(getX() + _speed);
        }
    } else if (direction == -1) {
        if (getX() > 0) {
            setX(getX() - _speed);
        }
    }
}