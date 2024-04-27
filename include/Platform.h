#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject {
  public:
    Platform(int x, int y, int width, int height, SDL_Color color, int speed)
        : GameObject(x, y, width, height, color), _speed(speed){};

    // Getters
    int getSpeed() const;

    // Setters
    void setSpeed(int speedX);

    // Methods

    virtual void draw(SDL_Renderer *renderer) override;

    void move(int direction, int windowWidth);

  private:
    int _speed;
};

#endif // PLATFORM_H