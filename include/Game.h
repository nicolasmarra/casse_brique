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

class Game {
  public:
    Game();
    ~Game();

    void run(std::string configuration);

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
    void checkBallBrickCollision();

    void loadBricksFromFile(const std::string &filename);

    void drawScore();

    void drawLives();

    void drawText(const std::string &text, int x, int y, int size,
                  SDL_Color color);

  private:
    void init(std::string configuration);
    void handleEvents();
    void update();
    void render();
    void clean();
    void createBricks(BrickType type);

    bool _isRunning;
    int _position_balle;
    int _score = 0;
    int _lives = 3;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    std::shared_ptr<Platform> _platform;
    std::vector<std::shared_ptr<Ball>> _ball;
    std::vector<std::shared_ptr<Brick>> _bricks;
};

#endif // GAME_H