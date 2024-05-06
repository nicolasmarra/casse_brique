#include "Brick.h"

int Brick::getResistance() const { return _resistance; }

int Brick::getContainsBall() const { return _containsBall; }

void Brick::setResistance(int resistance) { _resistance = resistance; }

void Brick::setContainsBall(int containsBall) { _containsBall = containsBall; }

void Brick::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);
    SDL_Rect rect = {static_cast<int>(getX()), static_cast<int>(getY()),
                     static_cast<int>(getWidth()),
                     static_cast<int>(getHeight())};
    SDL_RenderFillRect(renderer, &rect);
}

void Brick::changeColor(SDL_Renderer *renderer) {

    if (getResistance() == 1) {
        setColor(SDL_Color{255, 0, 0, 255});
    } else if (getResistance() == 2) {
        setColor(SDL_Color{0, 255, 0, 255});
    } else if (getResistance() == 3) {
        setColor(SDL_Color{0, 0, 255, 255});
    }
}

void Brick::setInvisible() {
    setWidth(0);
    setHeight(0);
}

/*
bool Brick::collideWithBall(double ballX, double ballY, double ballRadius) {

    if (ballX + ballRadius >= getX() &&
        ballX - ballRadius <= getX() + getWidth() &&
        ballY + ballRadius >= getY() &&
        ballY - ballRadius <= getY() + getHeight()) {

        if (ballY + ballRadius >= getY() &&
            ballY - ballRadius <= getY() + getHeight()) {
            setResistance(getResistance() - 1);
            if (getResistance() == 0) {

                setDestroyed(true);
                return true;
            }
        }

        if (ballX + ballRadius >= getX() &&
            ballX - ballRadius <= getX() + getWidth()) {
            setResistance(getResistance() - 1);
            if (getResistance() == 0) {

                setDestroyed(true);
                return true;
            }
        }
    }
}
*/