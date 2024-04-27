#include "Brick.h"

int Brick::getResistance() const { return _resistance; }

int Brick::getContainsBall() const { return _containsBall; }

void Brick::setResistance(int resistance) { _resistance = resistance; }

void Brick::setContainsBall(int containsBall) { _containsBall = containsBall; }

void Brick::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);
    SDL_Rect rect = {getX(), getY(), getWidth(), getHeight()};
    SDL_RenderFillRect(renderer, &rect);
}
