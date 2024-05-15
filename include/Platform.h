#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

/**
 * @brief Platform class
 *
 * @details This class represents the platform object in the game. It inherits
 * from the GameObject class.
 */
class Platform : public GameObject {
  public:
    /**
     * @brief Construct a new Platform object
     * @param x The x coordinate of the platform
     * @param y The y coordinate of the platform
     * @param width The width of the platform
     * @param height The height of the platform
     * @param color The color of the platform
     * @param speed The speed of the platform
     * @details This constructor initializes the platform object with the given
     */
    Platform(double x, double y, double width, double height, SDL_Color color,
             int speed)
        : GameObject(x, y, width, height, color), _speed(speed){};

    // Getters
    int getSpeed() const;

    // Setters
    void setSpeed(int speedX);

    // Methods

    /**
     * @brief Draw the platform object
     * @param renderer The SDL_Renderer to draw the platform on the screen
     */
    virtual void draw(SDL_Renderer *renderer) override;

    /**
     * @brief Move the platform object
     * @param direction The direction to move the platform
     * @param windowWidth The width of the window
     */
    void move(int direction, int windowWidth);

  private:
    int _speed; // The speed of the platform
};

#endif // PLATFORM_H