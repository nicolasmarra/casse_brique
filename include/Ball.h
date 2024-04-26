#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject {

  public:
    Ball(int x, int y, int width, int height, SDL_Color color, int speedX,
         int speedY, int resistance = 1)
        : GameObject(x, y, width, height, color), _speedX(speedX),
          _speedY(speedY), _resistance(resistance){};

    // Getters
    int getSpeedX() const;
    int getSpeedY() const;
    int getResistance() const;

    // Setters
    void setSpeedX(int speedX);
    void setSpeedY(int speedY);
    void setResistance(int resistance);

  private:
    int _speedX;
    int _speedY;
    int _resistance;
};

#endif // BALL_H