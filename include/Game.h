#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "PowerUp.h"
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

/**
 * @brief Game class
 *
 * @details This class represents the game object. It is responsible for
 * managing the game loop, handling events, updating the game state, rendering
 * the game objects, and cleaning up the game resources.
 */
class Game {
  public:
    // Constructors
    Game();
    ~Game();

    // Getters
    bool isRunning() const { return _isRunning; }
    SDL_Window *getWindow() const { return _window; }
    SDL_Renderer *getRenderer() const { return _renderer; }
    int getScore() const { return _score; }
    int getPosition_balle() const { return _position_balle; }
    int getLives() const { return _lives; }

    // Setters
    void setRunning(bool isRunning) { _isRunning = isRunning; }

    void setWindow(SDL_Window *window) { _window = window; }

    void setRenderer(SDL_Renderer *renderer) { _renderer = renderer; }

    void setScore(int score) { _score = score; }

    void setPosition_balle(int position_balle) {
        _position_balle = position_balle;
    }

    void setLives(int lives) { _lives = lives; }

    // Methods

    /**
     * @brief Run the game
     * @param configuration The configuration file path
     * @details This method initializes the game
     */
    void run(std::string configuration);

  private:
    /**
     * @brief Draw the game objects
     * @details This method draws the game objects on the screen
     */
    void drawScore();

    /**
     * @brief Draw the lives
     * @details This method draws the lives on the screen
     */
    void drawLives();

    /**
     * @brief Draw the text
     * @param text The text to draw
     * @param x The x coordinate of the text
     * @param y The y coordinate of the text
     * @param size The size of the text
     * @param color The color of the text
     * @details This method draws the text on the screen
     */
    void drawText(const std::string &text, int x, int y, int size,
                  SDL_Color color);

    /**
     * @brief Check if all the balls are down
     * @details This method checks if all the balls are down
     * @return True if all the balls are down, false otherwise
     * @details This method checks if all the balls are down
     * @return True if all the balls are down, false otherwise
     */
    bool isAllBallDown();

    /**
     * @brief Check if the game is over
     * @details This method checks if the game is over
     * @return True if the game is over, false otherwise
     */
    void applyPowerUp(std::shared_ptr<PowerUp> powerUp);

    /**
     * @brief Get the number of balls
     * @param isActive The state of the ball
     * @return The number of balls
     * @details This method returns the number of balls
     */
    int getNumberOfBall(bool isActive);

    /**
     * @brief Check the collision between the ball and the platform
     * @details This method checks if the ball collides with the platform and
     * the Ball
     */
    void checkBallBrickCollision();

    /**
     * @brief Check the collision between the ball and the platform
     * @details This method checks if the ball collides with the platform
     */
    void loadBricksFromFile(const std::string &filename);

    /**
     * @brief Check the collision between the ball and the platform
     * @details This method checks if the ball collides with the platform
     */
    void init(std::string configuration);

    /**
     * @brief Handle the events
     * @details This method handles the events
     */
    void handleEvents();

    /**
     * @brief Update the game objects
     * @details This method updates the game objects
     */
    void update();

    /**
     * @brief Render the game objects
     * @details This method renders the game objects
     */
    void render();

    /**
     * @brief Clean up the game resources
     * @details This method cleans up the game resources
     */
    void clean();

    /**
     * @brief Create the bricks
     * @param type The type of the brick
     * @details This method creates the bricks
     */
    void createBricks(BrickType type);

    bool _isRunning;                          /**< The state of the game */
    int _position_balle;                      /**< The position of the ball */
    int _score = 0;                           /**< The score of the game */
    int _lives = 3;                           /**< The lives of the player */
    SDL_Window *_window;                      /**< The SDL window */
    SDL_Renderer *_renderer;                  /**< The SDL renderer */
    std::shared_ptr<Platform> _platform;      /**< The platform object */
    std::vector<std::shared_ptr<Ball>> _ball; /**< The ball object */
    std::vector<std::shared_ptr<Brick>> _bricks;     /**< The brick object */
    std::vector<std::shared_ptr<PowerUp>> _powerUps; /**< The power up object */
};

#endif // GAME_H