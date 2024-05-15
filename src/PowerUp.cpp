#include "PowerUp.h"

double PowerUp::getSpeedX() const { return _speedX; }

double PowerUp::getSpeedY() const { return _speedY; }

void PowerUp::setSpeedX(double speedX) { _speedX = speedX; }

void PowerUp::setSpeedY(double speedY) { _speedY = speedY; }

void PowerUp::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);

    for (int i = getRadius() * -1; i <= getRadius(); i++) {

        for (int j = getRadius() * -1; j <= getRadius(); j++) {

            if (i * i + j * j <= getRadius() * getRadius())
                SDL_RenderDrawPoint(renderer, getX() + i, getY() + j);
        }
    }
}

void PowerUp::move(int windowWidth, int windowHeight) {

    setX(getX() + _speedX);
    setY(getY() + _speedY);

    if (getX() - getRadius() < 0 || getX() + getRadius() > windowWidth) {
        _speedX *= -1;
    }

    if (getY() - getRadius() < 0 || getY() + getRadius() > windowHeight) {
        _speedY *= -1;
    }
}

bool PowerUp::collideWithPlatform(double platformX, double platformY,
                                  double platformWidth, double platformHeight) {

    if (getX() + getRadius() >= platformX &&
        getX() - getRadius() <= platformX + platformWidth &&
        getY() + getRadius() >= platformY &&
        getY() - getRadius() <= platformY + platformHeight) {

        return true;
    }

    return false;
}

bool PowerUp::getIsActive() const { return _isActive; }

void PowerUp::setIsActive(bool isActive) { _isActive = isActive; }

void PowerUp::setInvisible() {
    setRadius(0);
    // couleur noire
    SDL_Color color = {0, 0, 0, 255};
    setColor(color);
}

PowerUpType PowerUp::getType() const { return _type; }

void PowerUp::setType(PowerUpType type) { _type = type; }

int PowerUp::getDuration() const { return _duration; }

void PowerUp::setDuration(int duration) { _duration = duration; }

bool PowerUp::getHasDuration() const { return _has_duration; }

void PowerUp::setHasDuration(bool has_duration) {
    _has_duration = has_duration;
}

bool PowerUp::getIsUsed() const { return _isUsed; }

void PowerUp::setIsUsed(bool isUsed) { _isUsed = isUsed; }