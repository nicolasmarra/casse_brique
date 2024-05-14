#include "Game.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PLATFORM_WIDTH 125
#define PLATFORM_HEIGHT 15
#define PLATFORM_SPEED 10

#define BALL_RADIUS 5
#define BALL_SPEED_X 0.01
#define BALL_SPEED_Y 0.03

#define BRICK_WIDTH 59
#define BRICK_HEIGHT 15

#define BRICKS_COUNT 88
#define BRICKS_PER_ROW 11
#define BRICKS_DISTANCE 15

Game::Game() : _isRunning(false), _window(nullptr), _renderer(nullptr) {}

Game::~Game() { clean(); }

void Game::run() {
    init();
    while (_isRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::init() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL_Init : " << SDL_GetError() << std::endl;
        _isRunning = false;
        return;
    }

    // Création de la fenêtre
    _window = SDL_CreateWindow("Casse-briques", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (_window == nullptr) {
        std::cerr << "Erreur SDL_CreateWindow : " << SDL_GetError()
                  << std::endl;
        _isRunning = false;
        return;
    }

    // Création du renderer
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (_renderer == nullptr) {
        std::cerr << "Erreur SDL_CreateRenderer : " << SDL_GetError()
                  << std::endl;
        _isRunning = false;
        return;
    }

    // Création de la plateforme et de la balle
    _platform = std::make_shared<Platform>(
        WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20, PLATFORM_WIDTH, PLATFORM_HEIGHT,
        SDL_Color{255, 255, 0, 255}, PLATFORM_SPEED);

    _ball.push_back(std::make_shared<Ball>(
        WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, BALL_RADIUS,
        SDL_Color{0, 255, 0, 255}, BALL_SPEED_X, BALL_SPEED_Y, 1));

    // Création des briques
    for (int i = 0; i < BRICKS_COUNT; i++) {
        int x = (i % BRICKS_PER_ROW) * (BRICK_WIDTH + BRICKS_DISTANCE);
        int y = (i / BRICKS_PER_ROW) * (BRICK_HEIGHT + BRICKS_DISTANCE) + 50;

        int resistance = rand() % 3 + 1;
        int randomBall = rand() % 100;
        bool containsBall = randomBall > 70 ? 1 : 0;

        SDL_Color color;
        switch (resistance) {
        case 1:
             // Couleur rouge pour une résistance de 1
            color = SDL_Color{255, 0, 0, 255};
            break;
        case 2:
             // Couleur verte pour une résistance de 2
            color = SDL_Color{0, 255, 0, 255};
            break;
        case 3:
            // Couleur bleue pour une résistance de 3
            color = SDL_Color{0, 0, 255, 255};
            break;
        }

        _bricks.push_back(
            std::make_shared<Brick>(x, y, BRICK_WIDTH, BRICK_HEIGHT, color,
                                    resistance, containsBall, RECTANGLE));
    }

    _isRunning = true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            _isRunning = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _platform->move(-1, WINDOW_WIDTH);
                break;
            case SDLK_RIGHT:
                _platform->move(1, WINDOW_WIDTH);
                break;
            }
        }
    }
}

void Game::update() {

    for (auto &ball : _ball) {
        ball->move(WINDOW_WIDTH, WINDOW_HEIGHT);
        ball->collideWithPlatform(_platform->getX(), _platform->getY(),
                                  _platform->getWidth(),
                                  _platform->getHeight());
        if (ball->getY() + ball->getRadius() > WINDOW_HEIGHT) {

            ball->setIsActive(false);
            ball->setSpeedX(0);
            ball->setSpeedY(0);
            ball->setInvisible();
            ball->setColor(SDL_Color{0, 0, 0, 255});
            ball->draw(_renderer);
        }
    }

    int count_balls_down = 0;
    for (auto &ball : _ball) {
        if (ball->getIsActive() == false)
            count_balls_down++;
    }
    if (count_balls_down == _ball.size()) {
        _isRunning = false;
        std::cout << "PERDU !" << std::endl;
    }

    int count_bricks_destroyed = 0;
    for (auto &brick : _bricks) {
        if (brick->getDestroyed() == true)
            count_bricks_destroyed++;
    }

    if (count_bricks_destroyed == _bricks.size()) {
        _isRunning = false;
        std::cout << "GAGNE !" << std::endl;
    }

    checkBallBrickCollision();
}

void Game::render() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    _platform->draw(_renderer);

    for (auto &ball : _ball) {
        ball->draw(_renderer);
    }

    for (auto &brick : _bricks) {
        brick->draw(_renderer);
    }

    SDL_RenderPresent(_renderer);
}

void Game::clean() { SDL_Quit(); }

void Game::checkBallBrickCollision() {
    for (auto &brick : _bricks) {

        if (brick->getDestroyed() == true)
            continue;

        for (auto &ball : _ball) {
            if (ball->getIsActive() == false)
                continue;

            if (ball->collideWithBrick(brick->getX(), brick->getY(),
                                       brick->getWidth(), brick->getHeight())) {

                brick->setResistance(brick->getResistance() - 1);
                if (brick->getResistance() == 0) {
                    brick->setDestroyed(true);
                    brick->setInvisible();
                    brick->draw(_renderer);
                    /*if (brick->getContainsBall() == 1) {
                        _ball.push_back(std::make_shared<Ball>(
                            brick->getX(), brick->getY(), BALL_RADIUS,
                            SDL_Color{0, 255, 0, 255}, BALL_SPEED_X,
                            BALL_SPEED_Y, 1));
                        break;
                    }*/
                }
                brick->changeColor(_renderer);
            }
        }
    }
}
