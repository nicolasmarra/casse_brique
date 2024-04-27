#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

class GameObject {

  public:
    // Constructors
    GameObject(int x, int y, int width, int height, SDL_Color color)
        : _x(x), _y(y), _width(width), _height(height), _color(color){};

    GameObject(int x, int y, double radius, SDL_Color color)
        : _x(x), _y(y), _radius(radius), _color(color){};

    // Getters
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    double getRadius() const;
    SDL_Color getColor() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    void setRadius(double radius);
    void setColor(SDL_Color color);

    // Methods
    virtual void draw(SDL_Renderer *renderer) = 0;

  private:
    int _x;
    int _y;
    int _width;
    int _height;
    double _radius;
    SDL_Color _color;
};

#endif // GAMEOBJECT_H