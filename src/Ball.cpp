#include "Ball.h"
#include <iostream>

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

void Ball::move(int windowWidth, int windowHeight) {

    setX(getX() + _speedX);
    setY(getY() + _speedY);

    if (getX() - getRadius() < 0 || getX() + getRadius() > windowWidth) {
        _speedX *= -1;
    }

    if (getY() - getRadius() < 0 || getY() + getRadius() > windowHeight) {
        _speedY *= -1;
    }
}

void Ball::collideWithPlatform(double platformX, double platformY,
                               double platformWidth, double platformHeight) {

    if (getX() + getRadius() >= platformX &&
        getX() - getRadius() <= platformX + platformWidth &&
        getY() + getRadius() >= platformY &&
        getY() - getRadius() <= platformY + platformHeight) {

        if (getY() + getRadius() >= platformY &&
            getY() - getRadius() <= platformY + platformHeight) {
            _speedY *= -1;
        }

        if (getX() + getRadius() >= platformX &&
            getX() - getRadius() <= platformX + platformWidth) {
            _speedX *= -1;
        }
    }
}

bool Ball::collideWithBrick(double brickX, double brickY, double brickWidth,
                            double brickHeight) {

    if (getX() + getRadius() >= brickX &&
        getX() - getRadius() <= brickX + brickWidth &&
        getY() + getRadius() >= brickY &&
        getY() - getRadius() <= brickY + brickHeight) {

        if (getY() + getRadius() >= brickY &&
            getY() - getRadius() <= brickY + brickHeight) {
            _speedY *= -1;
            return true;
        }

        if (getX() + getRadius() >= brickX &&
            getX() - getRadius() <= brickX + brickWidth) {
            _speedX *= -1;
            return true;
        }
    }

    return false;
}

bool Ball::getIsActive() const { return _isActive; }

void Ball::setIsActive(bool isActive) { _isActive = isActive; }

void Ball::setInvisible() { setRadius(0); }
