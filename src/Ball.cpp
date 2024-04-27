#include "Ball.h"

double Ball::getSpeedX() const { return _speedX; }

double Ball::getSpeedY() const { return _speedY; }

int Ball::getResistance() const { return _resistance; }

void Ball::setSpeedX(double speedX) { _speedX = speedX; }

void Ball::setSpeedY(double speedY) { _speedY = speedY; }

void Ball::setResistance(int resistance) { _resistance = resistance; }

void Ball::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);

    for (int i = getRadius() * -1; i <= getRadius(); i++) {

        for (int j = getRadius() * -1; j <= getRadius(); j++) {

            if (i * i + j * j <= getRadius() * getRadius())
                SDL_RenderDrawPoint(renderer, getX() + i, getY() + j);
        }
    }
}
