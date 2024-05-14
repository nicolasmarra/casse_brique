#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include <cmath>

class Ball : public GameObject {

  public:
    Ball(double x, double y, double radius, SDL_Color color, double speedX,
         double speedY, int resistance = 1)
        : GameObject(x, y, radius, color), _speedX(speedX), _speedY(speedY),
          _resistance(resistance){};

    // Getters
    double getSpeedX() const;
    double getSpeedY() const;
    int getResistance() const;
    bool getIsActive() const;

    // Setters
    void setSpeedX(double speedX);
    void setSpeedY(double speedY);
    void setResistance(int resistance);
    void setIsActive(bool isActive);

    // Methods
    virtual void draw(SDL_Renderer *renderer) override;

    void move(int windowWidth, int windowHeight);

    void collideWithPlatform(double platformX, double platformY,
                             double platformWidth, double platformHeight);

    bool collideWithBrick(double brickX, double brickY, double brickWidth,
                          double brickHeight);
    
    void setInvisible();

  private:
    double _speedX;
    double _speedY;
    int _resistance;
    bool _isActive = true;
};

#endif // BALL_H