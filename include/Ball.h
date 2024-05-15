#ifndef BALL_H
#define BALL_H

#include "Brick.h"
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
     * @param brickX The x coordinate of the brick
     * @param brickY The y coordinate of the brick
     * @param brickWidth The width of the brick
     * @param brickHeight The height of the brick
     * @param type The type of the brick
     * @return true if the ball object collides with the brick, false
     */
    bool collideWithBrick(double brickX, double brickY, double brickWidth,
                          double brickHeight, BrickType type);

    /**
     * @brief Set the ball object invisible
     */
    void setInvisible();

  private:
    /**
     * @brief Collide the ball object with the rectangle
     * @param rectangleX The x coordinate of the rectangle
     * @param rectangleY The y coordinate of the rectangle
     * @param rectangleWidth The width of the rectangle
     * @param rectangleHeight The height of the rectangle
     */

    bool collideWithRectangle(double rectangleX, double rectangleY,
                              double rectangleWidth, double rectangleHeight);

    /**
     * @brief Collide the ball object with the triangle
     * @param triangleX The x coordinate of the triangle
     * @param triangleY The y coordinate of the triangle
     * @param triangleWidth The width of the triangle
     * @param triangleHeight The height of the triangle
     * @return true if the ball object collides with the triangle, false
     *
     */
    bool collideWithTriangle(double triangleX, double triangleY,
                             double triangleWidth, double triangleHeight);

    /**
     * @brief Check if a point is inside a triangle
     * @param pt The point to check
     * @param v1 The first vertex of the triangle
     * @param v2 The second vertex of the triangle
     * @param v3 The third vertex of the triangle
     * @return true if the point is inside the triangle, false
     */
    bool pointInTriangle(SDL_Point pt, SDL_Point v1, SDL_Point v2,
                         SDL_Point v3);

    /**
     * @brief Check if a point is inside a rectangle
     * @param pt The point to check
     * @param v1 The first vertex of the rectangle
     * @param v2 The second vertex of the rectangle
     * @param v3 The third vertex of the rectangle
     * @param v4 The fourth vertex of the rectangle
     * @return true if the point is inside the rectangle, false
     */
    float sign(SDL_Point p1, SDL_Point p2, SDL_Point p3);

    /**
     * @brief Collide the ball object with the hexagon
     * @param hexagonX The x coordinate of the hexagon
     * @param hexagonY The y coordinate of the hexagon
     * @param hexagonWidth The width of the hexagon
     * @param hexagonHeight The height of the hexagon
     * @return true if the ball object collides with the hexagon, false
     */
    bool collideWithHexagon(double hexagonX, double hexagonY,
                            double hexagonWidth, double hexagonHeight);

    /**
     * @brief Calculate the angle of the ball object
     * @param brickX The x coordinate of the brick
     * @param brickY The y coordinate of the brick
     * @param brickWidth The width of the brick
     * @param brickHeight The height of the brick
     */
    void calculateAngle(double brickX, double brickY, double brickWidth,
                        double brickHeight);
    double _speedX; // Speed of the ball in the x direction
    double _speedY; // Speed of the ball in the y direction
    bool _isActive = true;
};

#endif // BALL_H