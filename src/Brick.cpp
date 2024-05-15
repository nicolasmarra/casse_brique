#include "Brick.h"

int Brick::getResistance() const { return _resistance; }

bool Brick::getContainsBall() const { return _containsBall; }

bool Brick::getContainsPowerUp() const { return _containsPowerUp; }

bool Brick::getDestroyed() const { return _isdestroyed; }

BrickType Brick::getType() const { return _type; }

void Brick::setResistance(int resistance) { _resistance = resistance; }

void Brick::setContainsBall(int containsBall) { _containsBall = containsBall; }

void Brick::setContainsPowerUp(bool containsPowerUp) {
    _containsPowerUp = containsPowerUp;
}

void Brick::setDestroyed(bool destroyed) { _isdestroyed = destroyed; }

void Brick::setType(BrickType type) { _type = type; }

void Brick::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, getColor().r, getColor().g, getColor().b,
                           getColor().a);

    // On dessine la brique selon son type
    switch (getType()) {
    case RECTANGLE:
        drawRectangle(renderer);
        break;
    case TRIANGLE:
        drawTriangle(renderer);
        break;
    case HEXAGON:
        drawHexagon(renderer);
        break;
    }
}

void Brick::drawRectangle(SDL_Renderer *renderer) {
    SDL_Rect rect = {static_cast<int>(getX()), static_cast<int>(getY()),
                     static_cast<int>(getWidth()),
                     static_cast<int>(getHeight())};
    SDL_RenderFillRect(renderer, &rect);
}

void Brick::drawTriangle(SDL_Renderer *renderer) {
    std::vector<SDL_Point> points = {
        {static_cast<int>(getX() + getWidth() / 2), static_cast<int>(getY())},
        {static_cast<int>(getX() + getWidth()),
         static_cast<int>(getY() + getHeight())},
        {static_cast<int>(getX()), static_cast<int>(getY() + getHeight())}};
    SDL_RenderDrawLines(renderer, points.data(), points.size());
    SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[0].x,
                       points[0].y);
}

void Brick::drawHexagon(SDL_Renderer *renderer) {
    std::vector<SDL_Point> points = {
        {static_cast<int>(getX() + getWidth() / 4), static_cast<int>(getY())},
        {static_cast<int>(getX() + 3 * getWidth() / 4),
         static_cast<int>(getY())},
        {static_cast<int>(getX() + getWidth()),
         static_cast<int>(getY() + getHeight() / 2)},
        {static_cast<int>(getX() + 3 * getWidth() / 4),
         static_cast<int>(getY() + getHeight())},
        {static_cast<int>(getX() + getWidth() / 4),
         static_cast<int>(getY() + getHeight())},
        {static_cast<int>(getX()), static_cast<int>(getY() + getHeight() / 2)}};
    SDL_RenderDrawLines(renderer, points.data(), points.size());
    SDL_RenderDrawLine(renderer, points[5].x, points[5].y, points[0].x,
                       points[0].y);
}

void Brick::changeColor(SDL_Renderer *renderer) {

    // On change la couleur de la brique selon sa résistance
    if (getResistance() == 1) {
        setColor(SDL_Color{255, 0, 0, 255});
    } else if (getResistance() == 2) {
        setColor(SDL_Color{0, 255, 0, 255});
    } else if (getResistance() == 3) {
        setColor(SDL_Color{0, 0, 255, 255});
    }
}

void Brick::setInvisible() {
    // On rend la brique invisible en réduisant complétement sa taille
    setWidth(0);
    setHeight(0);
    // couleur noire
    SDL_Color color = {0, 0, 0, 255};
    setColor(color);
}
