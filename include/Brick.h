#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include <vector>

// Enumeration of the different types of bricks
enum BrickType { RECTANGLE, TRIANGLE, HEXAGON };

/**
 * @brief Brick class
 *
 * @details This class represents the brick object in the game. It inherits from
 * the GameObject class.
 */
class Brick : public GameObject {

  public:
    // Constructors
    /**
     * @brief Construct a new Brick object
     * @param x The x coordinate of the brick
     * @param y The y coordinate of the brick
     * @param width The width of the brick
     * @param height The height of the brick
     * @param color The color of the brick
     * @param resistance The resistance of the brick
     * @param containsBall Whether the brick contains a ball
     * @param containsPowerUp Whether the brick contains a power-up
     * @param type The type of the brick
     * @details This constructor initializes the brick object with the given
     */
    Brick(double x, double y, double width, double height, SDL_Color color,
          int resistance, bool containsBall, bool containsPowerUp,
          BrickType type = RECTANGLE)
        : GameObject(x, y, width, height, color), _resistance(resistance),
          _containsBall(containsBall), _containsPowerUp(containsPowerUp),
          _type(type){};

    // Getters
    int getResistance() const;
    bool getContainsBall() const;
    bool getDestroyed() const;
    BrickType getType() const;
    bool getContainsPowerUp() const;

    // Setters
    void setResistance(int resistance);
    void setContainsBall(int containsBall);
    void setDestroyed(bool destroyed);
    void setType(BrickType type);
    void setContainsPowerUp(bool containsPowerUp);

    // Methods
    /**
     * @brief Draw the brick object
     * @param renderer The SDL_Renderer to draw the brick on
     */
    virtual void draw(SDL_Renderer *renderer) override;

    /**
     * @brief Change the color of the brick
     * @param renderer The SDL_Renderer to draw the brick on
     */
    void changeColor(SDL_Renderer *renderer);

    /**
     * @brief Collide the brick object with the ball
     * @param ballX The x coordinate of the ball
     * @param ballY The y coordinate of the ball
     * @param ballRadius The radius of the ball
     * @return bool Whether the brick collides with the ball
     */
    void setInvisible();

  private:
    /**
     * @brief Draw the rectangle brick object
     * @param renderer The SDL_Renderer to draw the brick on
     */
    void drawRectangle(SDL_Renderer *renderer);

    /**
     * @brief Draw the triangle brick object
     * @param renderer The SDL_Renderer to draw the brick on
     */
    void drawTriangle(SDL_Renderer *renderer);

    /**
     * @brief Draw the hexagon brick object
     * @param renderer The SDL_Renderer to draw the brick on
     */
    void drawHexagon(SDL_Renderer *renderer);

    int _resistance; // The resistance of the brick
    bool _containsBall;
    bool _containsPowerUp;
    bool _isdestroyed = false;
    BrickType _type = RECTANGLE; // The type of the brick
};

#endif // BRICK_H