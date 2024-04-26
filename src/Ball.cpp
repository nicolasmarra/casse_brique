#include "Ball.h"

int Ball::getSpeedX() const { return _speedX; }

int Ball::getSpeedY() const { return _speedY; }

int Ball::getResistance() const { return _resistance; }

void Ball::setSpeedX(int speedX) { _speedX = speedX; }

void Ball::setSpeedY(int speedY) { _speedY = speedY; }

void Ball::setResistance(int resistance) { _resistance = resistance; }
