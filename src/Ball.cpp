#include "Ball.h"
#include <iostream>

double Ball::getSpeedX() const { return _speedX; }

double Ball::getSpeedY() const { return _speedY; }

void Ball::setSpeedX(double speedX) { _speedX = speedX; }

void Ball::setSpeedY(double speedY) { _speedY = speedY; }

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

    double ballCenterX = getX();
    double ballCenterY = getY();
    if (ballCenterX + getRadius() >= platformX &&
        ballCenterX - getRadius() <= platformX + platformWidth &&
        ballCenterY + getRadius() >= platformY &&
        ballCenterY - getRadius() <= platformY + platformHeight) {

        double platformCenterX = platformX + platformWidth / 2.0;
        double platformCenterY = platformY + platformHeight / 2.0;

        double dx = ballCenterX - platformCenterX;
        double dy = ballCenterY - platformCenterY;

        double angle = atan2(dy, dx);

        double newAngle = M_PI - angle;

        double speed =
            sqrt(getSpeedX() * getSpeedX() + getSpeedY() * getSpeedY());

        setSpeedY(sin(newAngle) * speed);
        setSpeedX(cos(newAngle) * speed);
    }
}

bool Ball::collideWithBrick(double brickX, double brickY, double brickWidth,
                            double brickHeight) {

    double ballCenterX = getX();
    double ballCenterY = getY();
    double brickCenterX = brickX + brickWidth / 2.0;
    double brickCenterY = brickY + brickHeight / 2.0;

    if (getX() + getRadius() >= brickX &&
        getX() - getRadius() <= brickX + brickWidth &&
        getY() + getRadius() >= brickY &&
        getY() - getRadius() <= brickY + brickHeight) {

        double dx = ballCenterX - brickCenterX;
        double dy = ballCenterY - brickCenterY;

        double angle = atan2(dy, dx);

        double newAngle = M_PI - angle;

        double speed =
            sqrt(getSpeedX() * getSpeedX() + getSpeedY() * getSpeedY());
        setSpeedX(cos(newAngle) * speed);
        setSpeedY(sin(newAngle) * speed);

        return true; // La balle a frappé la brique
    }

    return false;
}

bool Ball::getIsActive() const { return _isActive; }

void Ball::setIsActive(bool isActive) { _isActive = isActive; }

void Ball::setInvisible() { setRadius(0); }
