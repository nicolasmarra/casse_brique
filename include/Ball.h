#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include <cmath>

/**
 * @brief Ball class
 *
 * @details This class represents the ball object in the game. It inherits from
 * the GameObject class.
 */
class Ball : public GameObject {

  public:
    // Constructors
    /**
     * @brief Construct a new Ball object
     * @param x The x coordinate of the ball
     * @param y The y coordinate of the ball
     * @param radius The radius of the ball
     * @param color The color of the ball
     * @param speedX The speed of the ball in the x direction
     * @param speedY The speed of the ball in the y direction
     * @details This constructor initializes the ball object with the given
     * parameters.
     */
    Ball(double x, double y, double radius, SDL_Color color, double speedX,
         double speedY)
        : GameObject(x, y, radius, color), _speedX(speedX), _speedY(speedY){};

    // Getters
    double getSpeedX() const;
    double getSpeedY() const;
    bool getIsActive() const;

    // Setters
    void setSpeedX(double speedX);
    void setSpeedY(double speedY);
    void setIsActive(bool isActive);

    // Methods
    /**
     * @brief Draw the ball object
     * @param renderer The SDL_Renderer to draw the ball on
     */
    virtual void draw(SDL_Renderer *renderer) override;

    /**
     * @brief Move the ball object
     * @param windowWidth The width of the window
     * @param windowHeight The height of the window
     */
    void move(int windowWidth, int windowHeight);

    /**
     * @brief Collide the ball object with the platform
     * @param platformX The x coordinate of the platform
     * @param platformY The y coordinate of the platform
     * @param windowWidth The width of the brick
     * @param windowHeight The height of the brick
     */
    void collideWithPlatform(double platformX, double platformY,
                             double platformWidth, double platformHeight);

    /**
     * @brief Collide the ball object with the brick
     * @param BrickX The x coordinate of the brick
     * @param BrickY The y coordinate of the brick
     * @param windowWidth The width of the brick
     * @param windowHeight The height of the brick
     */

    bool collideWithBrick(double brickX, double brickY, double brickWidth,
                          double brickHeight);

    /**
     * @brief Set the ball object invisible
     */
    void setInvisible();

  private:
    double _speedX;
    double _speedY;
    bool _isActive = true;
};

#endif // BALL_H