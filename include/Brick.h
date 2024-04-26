#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject {

  public:
    Brick(int x, int y, int width, int height, SDL_Color color, int resistance,
          bool containsBall)
        : GameObject(x, y, width, height, color), _resistance(resistance),
          _containsBall(containsBall){};

    // Getters
    int getResistance() const;
    int getContainsBall() const;

    // Setters
    void setResistance(int resistance);
    void setContainsBall(int containsBall);

  private:
    int _resistance;
    bool _containsBall;
};

#endif // BRICK_H