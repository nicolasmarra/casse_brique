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
                            double brickHeight, BrickType type)

{
    if (type == BrickType::RECTANGLE) {
        return collideWithRectangle(brickX, brickY, brickWidth, brickHeight);
    } else if (type == BrickType::TRIANGLE) {
        return collideWithRectangle(brickX, brickY, brickWidth, brickHeight);
    } else if (type == BrickType::HEXAGON) {
        return collideWithRectangle(brickX, brickY, brickWidth, brickHeight);
    }
    return false;
}

bool Ball::collideWithRectangle(double rectangleX, double rectangleY,
                                double rectangleWidth, double rectangleHeight) {

    double ballCenterX = getX();
    double ballCenterY = getY();
    double rectangleCenterX = rectangleX + rectangleWidth / 2.0;
    double rectangleCenterY = rectangleY + rectangleHeight / 2.0;

    if (getX() + getRadius() >= rectangleX &&
        getX() - getRadius() <= rectangleX + rectangleWidth &&
        getY() + getRadius() >= rectangleY &&
        getY() - getRadius() <= rectangleY + rectangleHeight) {

        calculateAngle(rectangleX, rectangleY, rectangleWidth, rectangleHeight);
        return true; // La balle a frappé la brique
    }

    return false;
}

bool Ball::collideWithTriangle(double triangleX, double triangleY,
                               double triangleWidth, double triangleHeight) {

    double ballCenterX = getX();
    double ballCenterY = getY();

    // Points du triangle (triangle droit aligné avec l'angle droit en
    // bas à  gauche)

    SDL_Point p1 = {static_cast<int>(triangleX),
                    static_cast<int>(triangleY + triangleHeight)};
    SDL_Point p2 = {static_cast<int>(triangleX), static_cast<int>(triangleY)};
    SDL_Point p3 = {static_cast<int>(triangleX + triangleWidth),
                    static_cast<int>(triangleY + triangleHeight)};

    // Vérifiez la collision avec le bas du triangle
    if (ballCenterY + getRadius() >= p1.y &&
        ballCenterY - getRadius() <= p1.y &&
        ballCenterX + getRadius() >= p1.x &&
        ballCenterX - getRadius() <= p3.x) {
        calculateAngle(triangleX, triangleY, triangleWidth, triangleHeight);
        return true;
    }

    // Vérifiez la collision avec les trois côtés du triangle
    if (pointInTriangle(
            {static_cast<int>(ballCenterX), static_cast<int>(ballCenterY)}, p1,
            p2, p3)) {

        calculateAngle(triangleX, triangleY, triangleWidth, triangleHeight);

        return true;
    }

    return false;
}

void Ball::calculateAngle(double brickX, double brickY, double brickWidth,
                          double brickHeight) {

    double dx = getX() - brickX;
    double dy = getY() - brickY;

    double angle = atan2(dy, dx);
    double newAngle = M_PI - angle;
    double speed = sqrt(getSpeedX() * getSpeedX() + getSpeedY() * getSpeedY());
    setSpeedX(cos(newAngle) * speed);
    setSpeedY(sin(newAngle) * speed);
}

bool Ball::collideWithHexagon(double hexagonX, double hexagonY,
                              double hexagonWidth, double hexagonHeight) {
    double ballCenterX = getX();
    double ballCenterY = getY();

    // Centre de l'hexagone
    double centerX = hexagonX + hexagonWidth / 2;
    double centerY = hexagonY + hexagonHeight / 2;
    double radius = hexagonWidth / 2;

    // Calculer les sommets de l'hexagone
    SDL_Point points[6];
    for (int i = 0; i < 6; ++i) {
        points[i] = {static_cast<int>(centerX + radius * cos(M_PI / 3 * i)),
                     static_cast<int>(centerY + radius * sin(M_PI / 3 * i))};
    }

    // Vérifiez la collision avec les six côtés de l'hexagone
    for (int i = 0; i < 6; ++i) {
        SDL_Point p1 = points[i];
        SDL_Point p2 = points[(i + 1) % 6];
        if (pointInTriangle(
                {static_cast<int>(ballCenterX), static_cast<int>(ballCenterY)},
                {static_cast<int>(centerX), static_cast<int>(centerY)}, p1,
                p2)) {
            calculateAngle(hexagonX, hexagonY, hexagonWidth, hexagonHeight);
            return true;
        }
    }

    return false;
}

bool Ball::pointInTriangle(SDL_Point pt, SDL_Point v1, SDL_Point v2,
                           SDL_Point v3) {
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

float Ball::sign(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Ball::getIsActive() const { return _isActive; }

void Ball::setIsActive(bool isActive) { _isActive = isActive; }

void Ball::setInvisible() {
    setRadius(0);
    // couleur noire
    SDL_Color color = {0, 0, 0, 255};
    setColor(color);
}
