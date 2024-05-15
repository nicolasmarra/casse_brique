#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"
#include <cmath>

// Enumération pour représenter les types de power-up
enum PowerUpType {
    BONUS_INCREASE_PLATFORM_LENGTH,
    BONUS_INCREASE_PLATFORM_SPEED,
    BONUS_EXTRA_LIFE,
    MALUS_DECREASE_PLATFORM_SPEED,
    MALUS_DECREASE_PLATFORM_LENGTH,
    MALUS_LOSE_LIFE
};

/**
 * @brief PowerUp class
 *
 * @details This class represents the power up object in the game. It inherits
 * from the GameObject class.
 */
class PowerUp : public GameObject {

  public:
    // Constructors
    /**
     * @brief Construct a new power up object
     * @param x The x coordinate of the power up
     * @param y The y coordinate of the power up
     * @param radius The radius of the power up
     * @param color The color of the power up
     * @param speedX The speed of the power up in the x direction
     * @param speedY The speed of the power up in the y direction
     * @param type The type of the power up
     * @details This constructor initializes the power up object with the given
     * parameters.
     */
    PowerUp(double x, double y, double radius, SDL_Color color, double speedX,
            double speedY, PowerUpType type)
        : GameObject(x, y, radius, color), _speedX(speedX), _speedY(speedY){};

    // Getters
    double getSpeedX() const;
    double getSpeedY() const;
    bool getIsActive() const;
    PowerUpType getType() const;
    int getDuration() const;
    bool getHasDuration() const;
    bool getIsUsed() const;

    // Setters
    void setSpeedX(double speedX);
    void setSpeedY(double speedY);
    void setIsActive(bool isActive);
    void setType(PowerUpType type);
    void setDuration(int duration);
    void setHasDuration(bool has_duration);
    void setIsUsed(bool isUsed);

    // Methods
    /**
     * @brief Draw the power up object
     * @param renderer The SDL_Renderer to draw the power up on
     */
    virtual void draw(SDL_Renderer *renderer) override;

    /**
     * @brief Move the power up object
     * @param windowWidth The width of the window
     * @param windowHeight The height of the window
     */
    void move(int windowWidth, int windowHeight);

    /**
     * @brief Collide the power up object with the platform
     * @param platformX The x coordinate of the platform
     * @param platformY The y coordinate of the platform
     * @param windowWidth The width of the brick
     * @param windowHeight The height of the brick
     * @return true if the power up object collides with the platform, false
     */
    bool collideWithPlatform(double platformX, double platformY,
                             double platformWidth, double platformHeight);

    /**
     * @brief Set the ball object invisible
     */
    void setInvisible();

  private:
    double _speedX;
    double _speedY;
    bool _has_duration = false;
    int _duration = 0;
    PowerUpType _type; // Type de power-up
    bool _isActive = false;
    bool _isUsed = false;
};

#endif // BALL_H