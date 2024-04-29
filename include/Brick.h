#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject {

  public:
    Brick(double x, double y, double width, double height, SDL_Color color,
          int resistance, bool containsBall)
        : GameObject(x, y, width, height, color), _resistance(resistance),
          _containsBall(containsBall){};

    // Getters
    int getResistance() const;
    int getContainsBall() const;
    bool getDestroyed() const { return _isdestroyed; }

    // Setters
    void setResistance(int resistance);
    void setContainsBall(int containsBall);
    void setDestroyed(bool destroyed) { _isdestroyed = destroyed; }

    // Methods
    virtual void draw(SDL_Renderer *renderer) override;
    void changeColor(SDL_Renderer *renderer);
    bool collideWithBall(double ballX, double ballY, double ballRadius);
    void setInvisible();

  private:
    int _resistance;
    bool _containsBall;
    bool _isdestroyed = false;
};

#endif // BRICK_H