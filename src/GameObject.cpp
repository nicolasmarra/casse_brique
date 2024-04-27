#include "GameObject.h"

double GameObject::getX() const { return _x; }

double GameObject::getY() const { return _y; }

double GameObject::getWidth() const { return _width; }

double GameObject::getHeight() const { return _height; }

double GameObject::getRadius() const { return _radius; }

SDL_Color GameObject::getColor() const { return _color; }

void GameObject::setX(double x) { _x = x; }

void GameObject::setY(double y) { _y = y; }

void GameObject::setWidth(double width) { _width = width; }

void GameObject::setHeight(double height) { _height = height; }

void GameObject::setRadius(double radius) { _radius = radius; }

void GameObject::setColor(SDL_Color color) { _color = color; }
