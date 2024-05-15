#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

/**
 * @brief GameObject class
 *
 * @details This class represents the game object. It is the base class for all
 * the game objects in the game.
 */
class GameObject {

  public:
    // Constructors
    /**
     * @brief Construct a new GameObject object
     * @param x The x coordinate of the game object
     * @param y The y coordinate of the game object
     * @param width The width of the game object
     * @param height The height of the game object
     * @param color The color of the game object
     * @details This constructor initializes the game object with the given
     */
    GameObject(double x, double y, double width, double height, SDL_Color color)
        : _x(x), _y(y), _width(width), _height(height), _color(color){};

    /**
     * @brief Construct a new GameObject object
     * @param x The x coordinate of the game object
     * @param y The y coordinate of the game object
     * @param radius The radius of the game object
     * @param color The color of the game object
     * @details This constructor initializes the game object with the given
     */

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
    /**
     * @brief Draw the game object
     * @param renderer The SDL_Renderer to draw the game object on the screen
     */
    virtual void draw(SDL_Renderer *renderer) = 0;

  private:
    double _x;        // The x coordinate of the game object
    double _y;        // The y coordinate of the game object
    double _width;    // The width of the game object
    double _height;   // The height of the game object
    double _radius;   // The radius of the game object
    SDL_Color _color; // The color of the game object
};

#endif // GAMEOBJECT_H