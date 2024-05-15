#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "PowerUp.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

class Game {
  public:
    Game();
    ~Game();

    void run();

    // Getters
    bool isRunning() const { return _isRunning; }
    SDL_Window *getWindow() const { return _window; }
    SDL_Renderer *getRenderer() const { return _renderer; }

    // Setters

    void setRunning(bool isRunning) { _isRunning = isRunning; }

    void setWindow(SDL_Window *window) { _window = window; }

    void setRenderer(SDL_Renderer *renderer) { _renderer = renderer; }

    // Methods
    void checkBallBrickCollision();

    void loadBricksFromFile(const std::string &filename);

  private:
    void init();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool _isRunning;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    std::shared_ptr<Platform> _platform;
    std::vector<std::shared_ptr<Ball>> _ball;
    std::vector<std::shared_ptr<Brick>> _bricks;
};

#endif // GAME_H