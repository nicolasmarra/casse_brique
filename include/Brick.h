#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include <vector>

enum BrickType { RECTANGLE, TRIANGLE, HEXAGON };

class Brick : public GameObject {

  public:
    Brick(double x, double y, double width, double height, SDL_Color color,
          int resistance, bool containsBall, BrickType type = RECTANGLE)
        : GameObject(x, y, width, height, color), _resistance(resistance),
          _containsBall(containsBall), _type(type){};

    // Getters
    int getResistance() const;
    int getContainsBall() const;
    bool getDestroyed() const;
    BrickType getType() const;

    // Setters
    void setResistance(int resistance);
    void setContainsBall(int containsBall);
    void setDestroyed(bool destroyed);
    void setType(BrickType type);

    // Methods
    virtual void draw(SDL_Renderer *renderer) override;

    void changeColor(SDL_Renderer *renderer);
    bool collideWithBall(double ballX, double ballY, double ballRadius);
    void setInvisible();

  private:
    void drawRectangle(SDL_Renderer *renderer);
    void drawTriangle(SDL_Renderer *renderer);
    void drawHexagon(SDL_Renderer *renderer);

    int _resistance;
    bool _containsBall;
    bool _isdestroyed = false;
    BrickType _type = RECTANGLE;
};

#endif // BRICK_H