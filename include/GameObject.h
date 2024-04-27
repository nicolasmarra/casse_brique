#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

class GameObject {

  public:
    // Constructors
    GameObject(double x, double y, double width, double height, SDL_Color color)
        : _x(x), _y(y), _width(width), _height(height), _color(color){};

    GameObject(double x, double y, double radius, SDL_Color color)
        : _x(x), _y(y), _radius(radius), _color(color){};

    // Getters
    double getX() const;
    double getY() const;
    double getWidth() const;
    double getHeight() const;
    double getRadius() const;
    SDL_Color getColor() const;

    // Setters
    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);
    void setRadius(double radius);
    void setColor(SDL_Color color);

    // Methods
    virtual void draw(SDL_Renderer *renderer) = 0;

  private:
    double _x;
    double _y;
    double _width;
    double _height;
    double _radius;
    SDL_Color _color;
};

#endif // GAMEOBJECT_H