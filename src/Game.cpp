#include "Game.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PLATFORM_WIDTH 125
#define PLATFORM_HEIGHT 15

#define BALL_RADIUS 5

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
    _platform = std::make_shared<Platform>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20,
                                           PLATFORM_WIDTH, PLATFORM_HEIGHT,
                                           SDL_Color{255, 255, 0, 255}, 5);

    _ball =
        std::make_shared<Ball>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, BALL_RADIUS,
                               SDL_Color{0, 255, 0, 255}, 0.03, 0.06, 1);

    // Création des briques
    for (int i = 0; i < BRICKS_COUNT; i++) {

        int x = (i % BRICKS_PER_ROW) * (BRICK_WIDTH + BRICKS_DISTANCE);
        int y = (i / BRICKS_PER_ROW) * (BRICK_HEIGHT + BRICKS_DISTANCE) + 50;

        int resistance = rand() % 3 + 1;
        bool containsBall = rand() % 2;

        SDL_Color color;
        switch (resistance) {
        case 1:
            color = SDL_Color{255, 0, 0, 255};
            break;
        case 2:
            color = SDL_Color{0, 255, 0, 255};
            break;
        case 3:
            color = SDL_Color{0, 0, 255, 255};
            break;
        }

        _bricks.push_back(std::make_shared<Brick>(
            x, y, BRICK_WIDTH, BRICK_HEIGHT, color, resistance, containsBall));
    }

    _isRunning = true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            _isRunning = false;
        }
    }
}

void Game::update() {}

void Game::render() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    _platform->draw(_renderer);
    _ball->draw(_renderer);

    for (auto &brick : _bricks) {
        brick->draw(_renderer);
    }

    SDL_RenderPresent(_renderer);
}

void Game::clean() { SDL_Quit(); }