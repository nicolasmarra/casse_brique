#include "GameObject.h"

int GameObject::getX() const { return _x; }

int GameObject::getY() const { return _y; }

int GameObject::getWidth() const { return _width; }

int GameObject::getHeight() const { return _height; }

SDL_Color GameObject::getColor() const { return _color; }

void GameObject::setX(int x) { _x = x; }

void GameObject::setY(int y) { _y = y; }

void GameObject::setWidth(int width) { _width = width; }

void GameObject::setHeight(int height) { _height = height; }

void GameObject::setColor(SDL_Color color) { _color = color; }
